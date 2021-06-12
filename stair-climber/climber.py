import time

import motors
import pictogram_centering
import pictogram_detector
import sensors
import tensor_setup
from camera import Camera
from path_finder import Pathfinder
from uart import Uart
from video_stream import VideoStream


class Climber:

    def __init__(self):
        self.uart = Uart()
        self.ultra_sonic = sensors.UltraSonic(self.uart)
        self.led = sensors.LED(self.uart)
        self.buttons = sensors.Buttons()

        self.mid_motor = motors.MidMotor(self.uart)
        self.outer_motors = motors.OuterMotors(self.uart)
        self.rotation = motors.StepperMotor(self.uart)
        self.lift = motors.LiftMotor(self.uart)

        self.picto_tensor_config = tensor_setup.TensorSetup("detect.tflite", "labelmap.txt")
        self.stair_tensor_config = tensor_setup.TensorSetup("detect_brick_v2.tflite", "labelmap_path.txt")

        self.picto_detector = pictogram_detector.PictogramDetector(self.picto_tensor_config)
        self.picto_centering = pictogram_centering.PictogramCentering(self.picto_tensor_config)
        self.path_finder = Pathfinder(self.stair_tensor_config)

        self.detected_pictogram = None
        self.path = None
        self.is_normal_driving = True
        self.touched = False
        # TODO update with correct position
        self.picto_dict = {
            "hammer": 1,
            "taco": 3,
            "ruler": 4,
            "paint": 5,
            "pen": 6
        }
        self.clockwise = False
        self.buttons.whatever_btn.when_pressed = self.__set_clockwise
        self.buttons.leftFront_btn.when_pressed = lambda: self.__stop_motors()
        self.buttons.leftBack_btn.when_pressed = lambda: self.__stop_motors()
        self.buttons.rightFront_btn.when_pressed = lambda: self.__stop_motors()
        self.buttons.rightBack_btn.when_pressed = lambda: self.__stop_motors()

    # Robot waits for start command
    def wait_for_start(self):
        print("ready waiting for start cmd")
        self.buttons.wait_for_startbutton()

    # Robot looks for and identifies the given pictogram
    def search_identify_pictogram(self):
        degree = 0
        while self.detected_pictogram is None and degree < 360:
            print("looking for pictogram")
            img_path = "/home/pi/Desktop/picto.jpg"
            # Take picture
            Camera.take_picture_to_path(img_path)
            # Analyze picture
            self.detected_pictogram = self.picto_detector.analyze_picture(img_path)
            # Retry on fail (should we turn the robot? Is this even needed?)
            if self.detected_pictogram is None:
                print("No Image recognized, retrying...")
                degree += 45
                self.rotation.go_to_degree_onground(degree)

        if self.detected_pictogram is None:
            print("not detected using ruler")
            self.detected_pictogram = "ruler"
        print("image recognized: " + self.detected_pictogram)

        self.led.set_green(200)
        self.rotation.go_to_degree_onground(0)

    def plan_path(self):
        print("starting path planning")
        self.lift.frontUp()
        img_path = "/home/pi/Desktop/stair.jpg"
        Camera.take_picture_to_path(img_path)
        matrix, start = self.path_finder.transform_image_to_matrix(img_path)
        self.path = self.path_finder.compute_path(matrix, (start, 6), (self.picto_dict.get(self.detected_pictogram), 0))
        # self.path = [(3, 6), (3, 5), (3, 4), (2, 4), (2, 3), (2, 2), (2, 1), (2, 0), (3, 0), (4, 0)]
        self.lift.frontDown()
        print(self.path)

    # Robot drives to stairs
    def drive_to_stairs(self):
        print("driving to stairs")
        speed = 254

        # drive forward
        self.lift.driveMode_middleUp()
        self.outer_motors.accelerate_forward(speed)
        distance_threshold = 70  # in cm

        # noop while robot is far from stairs
        while self.ultra_sonic.get_distance1() > distance_threshold \
                and self.ultra_sonic.get_distance2() > distance_threshold:
            time.sleep(0.2)
            pass

        # Closer than threshhold
        print("slowing down")
        time.sleep(0.5)
        self.outer_motors.accelerate_forward(0)

        self.lift.driveMode_middleUp()
        self.rotation.go_to_degree_inair(180)
        self.lift.driveMode_middleDown()

    # Robot climbs up stairs
    def climb_stairs(self):
        instructions = self.path_finder.transform_path(self.path)
        print(instructions)
        instructions_cnt = len(instructions) - 1
        for idx, instruction in enumerate(instructions):
            instructions_length = len(instruction)

            # Reset reference so robot drives straighter against stairs
            if idx == 1:
                self.lift.driveMode_middleUp()
                self.rotation.go_to_reference_inair()
                self.rotation.go_to_degree_inair(180)
                self.lift.driveMode_middleDown()

            if instructions_length == 1:
                print("going up directly")
            else:
                self.lift.driveMode_middleUp()
                self.rotation.go_to_degree_inair(90)
                self.lift.driveMode_middleDown()
                self.lift.rotationMode()
                if instruction[0] < instruction[1]:
                    print("going left then up ")
                    self.mid_motor.accelerate_backwards(254)
                elif instruction[0] > instruction[1]:
                    print("going right then up")
                    self.mid_motor.accelerate_forward(254)
                # Todo check this stuff
                # when there is resistance time must be longer
                time.sleep(1.2 * instructions_length)
                self.mid_motor.accelerate_forward(0)
                self.mid_motor.accelerate_backwards(0)
                if idx != len(instructions):
                    self.lift.lower_outer_axes()
                    self.lift.driveMode_middleUp()
                    self.rotation.go_to_degree_inair(180)

                if self.touched: print("I hit a brick or so")

            if instructions_cnt != idx:
                self.lift.climb_stair()

    def drive_into_flag(self):
        print("going to flag")

        self.lift.driveMode_middleUp()
        self.rotation.go_to_reference_inair()
        self.rotation.go_to_degree_inair(90)
        self.lift.driveMode_middleDown()
        self.lift.rotationMode()
        self.lift.frontUp()
        self.video_stream = VideoStream()
        self.video_stream.start()
        self.picto_centering.center_robot_on_pictogram(self.detected_pictogram, self.video_stream, self.mid_motor)
        self.lift.frontDown()
        self.lift.driveMode_middleUp()
        self.rotation.go_to_degree_inair(180)
        self.lift.driveMode_middleDown()
        self.lift.rotationMode()
        self.lift.lower_outer_axes()
        self.lift.frontUp()
        self.outer_motors.accelerate_forward(254)
        self.mid_motor.accelerate_forward(254)
        time.sleep(11)
        self.outer_motors.accelerate_forward(0)
        self.mid_motor.accelerate_forward(0)
        # Robot climbs on single stair

    def __set_clockwise(self):
        self.clockwise = True

    def __stop_motors(self):
        self.mid_motor.accelerate_forward(0)
        self.touched = True
