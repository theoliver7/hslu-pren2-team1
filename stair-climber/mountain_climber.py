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


class MountainClimber:

    def __init__(self):
        self.uart = Uart()
        self.ultra_sonic = sensors.UltraSonic(self.uart)
        self.led = sensors.LED(self.uart)
        self.buttons = sensors.Buttons()

        self.mid_motor = motors.MidMotor(self.uart)
        self.outer_motors = motors.OuterMotors(self.uart)
        self.rotation = motors.StepperMotor(self.uart)
        self.lift = motors.LiftMotor(self.uart)

        self.picto_tensor_config = tensor_setup.TensorSetup("detect_picto_v2.tflite", "labelmap.txt")
        self.stair_tensor_config = tensor_setup.TensorSetup("detect_brick_v2.tflite", "labelmap_path.txt")

        self.picto_detector = pictogram_detector.PictogramDetector(self.picto_tensor_config)
        self.picto_centering = pictogram_centering.PictogramCentering(self.picto_tensor_config)
        self.path_finder = Pathfinder(self.stair_tensor_config)

        self.video_stream = VideoStream()

        self.detected_pictogram = None
        self.path = None
        self.is_normal_driving = True
        self.touched = False
        # TODO update with correct position
        self.picto_dict = {
            "Hammer": 1,
            "Taco": 3,
            "Ruler": 4,
            "Paint": 5,
            "Pen": 6
        }

        self.buttons.whatever_btn.when_pressed = lambda: print("Hello, WhateverButton start!")
        self.buttons.leftFront_btn.when_pressed = lambda: self.mid_motor.accelerate_forward(0); self.touched = True
        self.buttons.leftBack_btn.when_pressed = lambda: self.mid_motor.accelerate_forward(0); self.touched = True
        self.buttons.rightFront_btn.when_pressed = lambda: self.mid_motor.accelerate_forward(0);self.touched = True
        self.buttons.rightBack_btn.when_pressed = lambda: self.mid_motor.accelerate_forward(0);self.touched = True

    # Robot waits for start command
    def wait_for_start(self):
        print("ready waiting for start cmd")
        self.buttons.wait_for_startbutton()

    # Robot looks for and identifies the given pictogram
    def search_identify_pictogram(self):
        print("looking for pictogram")
        img_path = "/home/pi/Desktop/picto.jpg"
        # Take picture
        Camera.take_picture_to_path(img_path)

        # Analyze picture
        self.detected_pictogram = self.picto_detector.analyze_picture(img_path)
        # Retry on fail (should we turn the robot? Is this even needed?)
        if self.detected_pictogram is None:
            print("No Image recognized, retrying...")
            self.search_identify_pictogram()

        print("image recognized: " + self.detected_pictogram)
        self.led.set_green(200)
        self.rotation.go_to_reference_onground()

    def plan_path(self):
        print("starting path planning")
        img = "/home/pi/Desktop/stair.jpg"
        # img = "C:/dev/git/pren2-team1/stair-climber/test/images/stair8.jpg"
        # self.detectedPictogram = "Hammer"
        Camera.take_picture_to_path(img)
        matrix, start = self.path_finder.transform_image_to_matrix(img)
        # TODO determine start position
        self.path = self.path_finder.compute_path(matrix, (start, 6), (self.picto_dict.get(self.detected_pictogram), 0))
        print(self.path)

    # Robot drives to stairs
    def drive_to_stairs(self):
        print("driving to stairs")
        speed = 254

        # drive forward
        self.lift.driveMode_middleUp()
        time.sleep(3)
        self.outer_motors.accelerate_forward(speed)
        distance_threshhold = 70  # in cm

        # noop while robot is far from stairs
        while self.ultra_sonic.get_distance1() > distance_threshhold \
                and self.ultra_sonic.get_distance2() > distance_threshhold:
            time.sleep(0.5)
            pass

        # Closer than threshhold
        print("slowing down")
        self.outer_motors.accelerate_forward(0)

    # Robot climbs up stairs
    # TODO: Number of stairs from image-recognition
    def climb_stairs(self):
        instructions = self.__transform_path()
        print(instructions)
        instructions_cnt = len(instructions) - 1
        for idx, instruction in enumerate(instructions):
            instructions_length = len(instruction)
            if instructions_length == 1:
                print("going up directly")
            else:
                degree = 0
                if instruction[0] < instruction[1]:
                    print("going right then up ")
                    degree = 90
                elif instruction[0] > instruction[1]:
                    print("going left then up")
                    degree = 270
                # Todo check this stuff

                self.lift.driveMode_middleUp()
                self.rotation.go_to_degree_inair(degree)
                self.lift.driveMode_middleDown()
                self.lift.rotationMode()
                self.mid_motor.accelerate_forward(100)
                time.sleep(1 * instructions_length)
                self.mid_motor.accelerate_forward(0)
                self.lift.lower_outer_axes()
                self.lift.driveMode_middleUp()
                self.rotation.go_to_reference_inair()
                if self.touched: print("I hit a brick or so")

            if instructions_cnt != idx:
                self.__climb_one_stair()

    def drive_into_flag(self):
        print("going to flag")
        self.lift.driveMode_middleUp()
        self.rotation.go_to_degree_inair(90)
        self.lift.driveMode_middleDown()
        self.lift.rotationMode()
        self.video_stream.start()
        self.picto_centering.center_robot_on_pictogram(self.detected_pictogram,self.video_stream, self)

        # Robot climbs on single stair
    def __climb_one_stair(self):
        # self.__find_climable_position()
        print("start climbing to next step")
        self.lift.climb_stair()

    # Robot finds open path and positions himself in front ready to climb the next step
    # TODO: Find position by looking at PathFinding Matrix
    def __find_climable_position(self):
        print("looking for climable position")
        # How do we know how far to the left/right we can go infront of the first step
        clear_threshhold = 10
        speed = 200

    def __transform_path(self):
        tmp_step = 99
        tmp_step_directions = None
        list_of_instructions = list()
        for step in self.path:
            if tmp_step != step[1]:
                if tmp_step_directions is not None: list_of_instructions.append(tmp_step_directions)
                tmp_step_directions = list()
                tmp_step = step[1]
                tmp_step_directions.append(step[0])
            else:
                tmp_step_directions.append(step[0])
        list_of_instructions.append(tmp_step_directions)

        return list_of_instructions
