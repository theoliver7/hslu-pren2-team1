import time

from datetime import time

import motors
import object_detector
import sensors
import tensor_setup
import video_stream


## TODO
# Is getting sensor data inside a while-loop to much/to fast?

class MountainClimber:
    is_normal_driving = True
    ultra_sonic = sensors.UltraSonic()
    buttons = sensors.Buttons()

    midMotor = motors.MidMotor()
    frontMotor = motors.FrontMotor()
    backMotor = motors.BackMotor()
    outerMotors = motors.OuterMotors()

    rotation = motors.StepperMotor()
    lift = motors.LiftMotor()

    tensorConfig = tensor_setup.TensorSetup()
    videoStream = video_stream.VideoStream(resolution=(1280, 720), framerate=30).start()
    objectDetector = object_detector.ObjectDetector(tensorConfig)
    detectedPictogram = None

    # Robot waits for start command
    def wait_for_start(self):
        self.buttons.wait_for_startbutton()

    # Robot looks for and identifies the given pictogram
    def search_identify_pictogram(self):
        # Start Video Stream
        self.videoStream.start()

        # Look for Object for x seconds
        self.rotationDegrees = 0
        while self.detectedPictogram is None: 
            self.detectedPictogram = self.objectDetector.analyzeVideo(self.videoStream, 5)

            # If not pictorgram found, try again
            time.sleep(1)

        # Stop the Video Stream
        self.videoStream.stop()

    # Robot drives to stairs
    def drive_to_stairs(self):
        speed = 20

        # drive forward
        self.outerMotors.accelerate_forward(speed)
        distance_threshhold = 10 # in cm

        # noop while robot is far from stairs
        while self.ultra_sonic.get_distance1() > distance_threshhold:
            pass

        # TODO: maybe
        # Do we need to straighten the robot here or will driving against the stairs already do that?

        # Closer than threshhold
        self.outerMotors.accelerate_forward(10)
        time.sleep(500) # maybe drive a little further to make sure we are touching the stairs?
        self.outerMotors.accelerate_forward(0)

    # Robot climbs up stairs
    def climb_stairs(self):
        numberOfStairs = 5 

        for i in range(numberOfStairs + 1):
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
            if not (self.ultra_sonic.get_distance1() > clear_threshhold) and not (self.ultra_sonic.get_distance2() > clear_threshhold):
                # Rotate robot so we can drive to either side
                self.__sideways_driving()

                # Adjust position slowly until sensor show free path
                self.midMotor.accelerate_forward(speed)

                # Triangle doesnt detect brick and path is not found to be clear (driving to right)
                while not (self.buttons.is_rightBack_pressed() or self.buttons.is_rightFront_pressed()) or not path_is_clear:
                    if (self.ultra_sonic.get_distance1() < clear_threshhold) and (self.ultra_sonic.get_distance2() < clear_threshhold):
                        path_is_clear = True

                # No path found - drive to other side
                self.midMotor.accelerate_backwards(speed)
                while not (self.buttons.is_leftBack_pressed() or self.buttons.is_leftFront_pressed()) or not path_is_clear:
                    if (self.ultra_sonic.get_distance1() < clear_threshhold) and (self.ultra_sonic.get_distance2() < clear_threshhold):
                        path_is_clear = True
            else: 
                path_is_clear = True

        # Put Robot in normal driving position and climb next step
        if not is_normal_driving:
            self.__normal_driving()

        self.__climb()
        
    # Robot climbs the next step
    def __climb(self):
        speed = 10

        # 1 - Lift first segment and place on next step
        self.lift.move_front_up(speed)

        ## TODO when to stop?
        self.midMotor.accelerate_forward(speed)
        time.sleep(500)
        self.midMotor.accelerate_forward(0)

        # TODO Sensor for detecting touching the floor is not defined? will this automatically stop?
        self.lift.move_front_down(speed)

        # 2 - Lift middle segment and place on next step
        ## Move both segmens at same time (up & down)
        ## Both Front and Back motor at same time
        self.lift.move_frontUp_BackDown(speed)

        ## TODO when to stop?
        self.outerMotors.accelerate_forward(speed)
        time.sleep(500)
        self.outerMotors.accelerate_forward(0)

        # 3 - Lift last segment and place on next step 
        self.lift.move_back_up(speed)

        ## TODO when to stop?
        self.midMotor.accelerate_forward(speed)
        time.sleep(500)
        self.midMotor.accelerate_forward(0)

        self.lift.move_back_down()

    # Robot enters normal driving mode (meaning: mid)
    def __normal_driving(self): 
        speed = 50
        # 1 - Lift middle segment in air, outer segments on ground
        self.lift.move_back_down(speed)
        self.lift.move_front_down(speed)

        # 2 - rotate middle segment by 90°
        self.rotation.go_to_reference()

        # 3 - Lift outer segments in air, middle segment on ground
        self.lift.move_back_up(speed)
        self.lift.move_front_up(speed)

        is_normal_driving = True

    # Robot enters sideways driving mode (meaning: only middle segment down)
    def __sideways_driving(self):
        speed = 50
        # 1 - Lift middle segment in air, outer segments on ground
        self.lift.move_back_down(speed)
        self.lift.move_front_down(speed)

        # 2 - rotate middle segment by 90°
        self.rotation.go_to_degree(90)

        # 3 - Lift outer segments in air, middle segment on ground
        self.lift.move_back_up(speed)
        self.lift.move_front_up(speed)

        is_normal_driving = False



    
