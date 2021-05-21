import time

from datetime import time
from uart import Uart

import motors
import object_detector
import sensors
import tensor_setup
import video_stream

class MountainClimber:
    uart = Uart()

    ultra_sonic = sensors.UltraSonic(uart)
    led = sensors.LED(uart)
    buttons = sensors.Buttons()

    mid_motor = motors.MidMotor(uart)
    outer_motors = motors.OuterMotors(uart)
    rotation = motors.StepperMotor(uart)
    lift = motors.LiftMotor(uart)

    tensor_config = tensor_setup.TensorSetup()
    objectDetector = object_detector.ObjectDetector(tensor_config)
    detectedPictogram = None
    is_normal_driving = True

    # Robot waits for start command
    def wait_for_start(self):
        self.buttons.wait_for_startbutton()

    # Robot looks for and identifies the given pictogram
    def search_identify_pictogram(self):
        print("Looking for pictogram")
        img_path = "/home/pi/Desktop/picto.jpg"
        # Take picture
        self.objectDetector.take_picture(img_path)

        #Analyze picture
        self.detectedPictogram = self.objectDetector.analyze_picture(img_path)
        # Retry on fail (should we turn the robot? Is this even needed?)
        if self.detectedPictogram is None:
            print("No Image recognized, retrying...")
            self.search_identify_pictogram()
        
        
        print("Image recognized: " + self.detectedPictogram)
        self.led.set_green(200)

    # Robot drives to stairs
    def drive_to_stairs(self):
        print("Driving to stairs")
        speed = 254

        # drive forward
        self.rotation.go_to_reference_onground()
        self.lift.driveMode_middleUp()
        self.outer_motors.accelerate_forward(speed)
        distance_threshhold = 5  # in cm

        # noop while robot is far from stairs
        while self.ultra_sonic.get_distance1() > distance_threshhold:
            pass

        # Closer than threshhold
        self.outer_motors.accelerate_forward(100)
        time.sleep(500)  # maybe drive a little further to make sure we are touching the stairs?
        self.outer_motors.accelerate_forward(0)

    # Robot climbs up stairs
    #TODO: Number of stairs from image-recognition
    def climb_stairs(self):
        number_of_stairs = 6

        for i in range(number_of_stairs + 1):
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
