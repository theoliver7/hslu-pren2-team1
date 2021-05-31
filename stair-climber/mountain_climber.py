import time

import motors
import object_detector
import sensors
import tensor_setup
from camera import Camera
from path_finder import Pathfinder
from uart import Uart


class MountainClimber:
    uart = Uart()

    ultra_sonic = sensors.UltraSonic(uart)
    led = sensors.LED(uart)
    buttons = sensors.Buttons()

    mid_motor = motors.MidMotor(uart)
    outer_motors = motors.OuterMotors(uart)
    rotation = motors.StepperMotor(uart)
    lift = motors.LiftMotor(uart)

    picto_tensor_config = tensor_setup.TensorSetup("detect.tflite", "labelmap.txt")
    stair_tensor_config = tensor_setup.TensorSetup("model_optimize2_V8.tflite", "labelmap_path.txt")

    object_detector = object_detector.PictogramDetector(picto_tensor_config)
    path_finder = Pathfinder(stair_tensor_config)

    detectedPictogram = None
    path = None
    is_normal_driving = True
    # TODO update with correct position
    picto_dict = {
        "Hammer": 1,
        "Taco": 3,
        "Ruler": 4,
        "Paint": 5,
        "Pen": 6
    }

    # Robot waits for start command
    def wait_for_start(self):
        self.buttons.wait_for_startbutton()

    # Robot looks for and identifies the given pictogram
    def search_identify_pictogram(self):
        print("Looking for pictogram")
        img_path = "/home/pi/Desktop/picto.jpg"
        # Take picture
        Camera.take_picture_to_path(img_path)

        # Analyze picture
        self.detectedPictogram = self.object_detector.analyze_picture(img_path)
        # Retry on fail (should we turn the robot? Is this even needed?)
        if self.detectedPictogram is None:
            print("No Image recognized, retrying...")
            self.search_identify_pictogram()

        print("Image recognized: " + self.detectedPictogram)
        self.led.set_green(200)
        self.rotation.go_to_reference_onground()

    def plan_path(self):
        print("Starting path planning")
        img = "/home/pi/Desktop/stair.jpg"
        # img = "test/images/stair8.jpg"
        self.detectedPictogram = "Hammer"
        Camera.take_picture_to_path(img)
        matrix = self.path_finder.transform_image_to_matrix(img)
        # TODO determine start position
        self.path = self.path_finder.compute_path(matrix, (4, 6), (self.picto_dict.get(self.detectedPictogram), 0))
        print(self.path)

    # Robot drives to stairs
    def drive_to_stairs(self):
        print("Driving to stairs")
        speed = 254

        # drive forward
        self.lift.driveMode_middleUp()
        time.sleep(3)
        self.outer_motors.accelerate_forward(speed)
        distance_threshhold = 70  # in cm

        # noop while robot is far from stairs
        while self.ultra_sonic.get_distance1() > distance_threshhold and self.ultra_sonic.get_distance2() > distance_threshhold:
            time.sleep(0.5)
            pass

        # Closer than threshhold
        print("slowing down")
        self.outer_motors.accelerate_forward(0)

    # Robot climbs up stairs
    # TODO: Number of stairs from image-recognition
    def climb_stairs(self):
        number_of_stairs = 6
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

            if instructions_cnt != idx:
                self.__climb_one_stair()

    # Robot climbs on single stair
    def __climb_one_stair(self):
        # self.__find_climable_position()
        print("Start climbing to next step")
        self.lift.climb_stair()

    # Robot finds open path and positions himself in front ready to climb the next step
    # TODO: Find position by looking at PathFinding Matrix 
    def __find_climable_position(self):
        print("Looking for climable position")
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
