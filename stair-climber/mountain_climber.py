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
    video_stream = video_stream.VideoStream(resolution=(1280, 720), framerate=30).start()
    objectDetector = object_detector.ObjectDetector(tensor_config)
    detectedPictogram = None
    is_normal_driving = True

    # Robot waits for start command
    def wait_for_start(self):
        self.buttons.wait_for_startbutton()

    # Robot looks for and identifies the given pictogram
    def search_identify_pictogram(self):
        # Start Video Stream
        self.video_stream.start()

        # Look for Object for x seconds
        self.rotationDegrees = 0
        while self.detectedPictogram is None:
            self.detectedPictogram = self.objectDetector.analyzeVideo(self.video_stream, 5)

            # If not pictorgram found, try again
            time.sleep(1)

        # Stop the Video Stream
        self.video_stream.stop()

    # Robot drives to stairs
    def drive_to_stairs(self):
        speed = 20

        # drive forward
        self.outer_motors.accelerate_forward(speed)
        distance_threshhold = 10  # in cm

        # noop while robot is far from stairs
        while self.ultra_sonic.get_distance1() > distance_threshhold:
            pass

        # TODO: maybe
        # Do we need to straighten the robot here or will driving against the stairs already do that?

        # Closer than threshhold
        self.outer_motors.accelerate_forward(10)
        time.sleep(500)  # maybe drive a little further to make sure we are touching the stairs?
        self.outer_motors.accelerate_forward(0)

    # Robot climbs up stairs
    def climb_stairs(self):
        number_of_stairs = 5

        for i in range(number_of_stairs + 1):
            self.__climb_one_stair()

    # Robot climbs on single stair
    def __climb_one_stair(self):
        self.__find_climable_position()
        self.__climb()

    # Robot finds open path and positions himself in front ready to climb the next step
    def __find_climable_position(self):
        # How do we know how far to the left/right we can go infront of the first step
        clear_threshhold = 10
        path_is_clear = False
        speed = 10

        # If Path is blocked move sideways
        while not path_is_clear:
            if not (self.ultra_sonic.get_distance1() > clear_threshhold) and not (
                    self.ultra_sonic.get_distance2() > clear_threshhold):
                # Rotate robot so we can drive to either side
                self.__sideways_driving()

                # Adjust position slowly until sensor show free path
                self.mid_motor.accelerate_forward(speed)

                # Triangle doesnt detect brick and path is not found to be clear (driving to right)
                while not (
                        self.buttons.is_rightBack_pressed() or self.buttons.is_rightFront_pressed()) or not path_is_clear:
                    if (self.ultra_sonic.get_distance1() < clear_threshhold) and (
                            self.ultra_sonic.get_distance2() < clear_threshhold):
                        path_is_clear = True

                # No path found - drive to other side
                self.mid_motor.accelerate_backwards(speed)
                while not (
                        self.buttons.is_leftBack_pressed() or self.buttons.is_leftFront_pressed()) or not path_is_clear:
                    if (self.ultra_sonic.get_distance1() < clear_threshhold) and (
                            self.ultra_sonic.get_distance2() < clear_threshhold):
                        path_is_clear = True
            else:
                path_is_clear = True

        # Put Robot in normal driving position and climb next step
        if not self.is_normal_driving:
            self.__normal_driving()

        self.__climb()

    # Robot climbs the next step
    def __climb(self):
        speed = 10

        # 1 - Lift first segment and place on next step
        self.lift.move_front_up(speed)

        ## TODO when to stop?
        self.mid_motor.accelerate_forward(speed)
        time.sleep(500)
        self.mid_motor.accelerate_forward(0)

        # TODO Sensor for detecting touching the floor is not defined? will this automatically stop?
        self.lift.move_front_down(speed)

        # 2 - Lift middle segment and place on next step
        ## Move both segmens at same time (up & down)
        ## Both Front and Back motor at same time
        self.lift.move_frontDown_BackUp(speed)

        ## TODO when to stop?
        self.outer_motors.accelerate_forward(speed)
        time.sleep(500)
        self.outer_motors.accelerate_forward(0)

        # 3 - Lift last segment and place on next step 
        self.lift.move_back_up(speed)

        ## TODO when to stop?
        self.mid_motor.accelerate_forward(speed)
        time.sleep(500)
        self.mid_motor.accelerate_forward(0)

        self.lift.move_back_down()

    # Robot enters normal driving mode (meaning: mid)
    def __normal_driving(self):
        speed = 50
        # 1 - Lift middle segment in air, outer segments on ground
        self.lift.move_both_down(speed)

        # 2 - rotate middle segment by 90
        self.rotation.go_to_reference()

        # 3 - Lift outer segments in air, middle segment on ground
        self.lift.move_both_up(speed)

        self.is_normal_driving = True

    # Robot enters sideways driving mode (meaning: only middle segment down)
    def __sideways_driving(self):
        speed = 50
        # 1 - Lift middle segment in air, outer segments on ground
        self.lift.move_both_down(speed)

        # 2 - rotate middle segment by 90
        self.rotation.go_to_degree_inair(90)

        # 3 - Lift outer segments in air, middle segment on ground
        self.lift.move_both_up(speed)

        self.is_normal_driving = False
