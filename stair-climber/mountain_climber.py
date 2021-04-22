import motors
import sensors
import video_stream
import object_detector
import time


## TODO
# Is getting sensor data inside a while-loop to much/to fast?

class MountainClimber:
    ultra_sonic = sensors.UltraSonic()
    buttons = sensors.Buttons()

    midMotor = motors.MidMotor()
    frontMotor = motors.FrontMotor()
    backMotor = motors.BackMotor()
    outerMotors = motors.OuterMotors()

    rotation = motors.StepperMotor()
    lift = motors.LiftMotor()

    videoStream = video_stream.VideoStream()
    objectDetector = object_detector.ObjectDetector()
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
            self.detectedPictogram = objectDetector.analyzeVideo(videoStream, 5)

            # If no Object found, turn by x Degrees. If Object found, return to starting Position
            if self.detectedPictogram is None: 
                self.rotationDegrees += 30
                self.rotation.go_to_degree(rotationDegrees)
            else:
                self.rotation.go_to_reference()
            time.sleep(1)

        # Stop the Video Stream
        self.videoStream.stop()

    # Robot drives to stairs
    def drive_to_stairs(self):
        # are we able to just drive straight or does the robot have to dodge the flag or alter his path otherwise
        # is this possible with the UltraSonic sensors?

        # drive forward
        self.frontMotor.accelerate()
        distance_threshhold = 3.1 # in cm, 3 is minimal value

        # noop while robot is far from stairs
        while self.ultra_sonic.get_distance1() > distance_threshhold:
            pass

        # Closer than threshhold
        # maybe drive a little further to make sure we are touching the stairs?
        self.frontMotor.stop()

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

        # 1 - Check if path is blocked
        if (self.ultra_sonic.get_distance1() > clear_threshhold) and (self.ultra_sonic.get_distance2() > clear_threshhold):
            # Path is free, can start the climbing 
            self.__climb_next_step()
        else:
            ## Should we check if there is a block first? will the rotation push the block?
            # Rotate robot so we can drive to either side
            self.__sideways_driving()
            # Adjust position slowly until sensor show free path

            # Put Robot in normal driving position and climb next step
            self.__normal_driving()
            self.__climb_next_step()
        
    # Robot climbs the next step
    def __climb(self):
        # 1 - Lift first segment and place on next step
        self.lift.move_front_up()
        self.midMotor.accelerate()
        ## TODO when to stop?
        ## TODO how far down do i move front?

        # 2 - Lift middle segment and place on next step
        ## Move both segmens at same time (up & down)
        ## Both Front and Back motor at same time
        self.lift.move_frontUp_BackDown()
        self.outerMotors.accelerate()
        ## TODO when to stop?

        # 3 - Lift last segment and place on next step 
        self.lift.move_back_up()
        self.midMotor.accelerate()
        ## TODO when to stop?
        self.lift.move_back_down()

    # Robot enters normal driving mode (meaning: all segments down, reference position)
    def __normal_driving(self): 
        # 1 - Turn Robot to starting position
        self.rotation.go_to_reference()
        # 2 - lower both outer segments
        self.lift.move_back_down()
        self.lift.move_front_down()

    # Robot enters sideways driving mode (meaning: only middle segment down, 90° turned)
    def __sideways_driving(self):
        # 1 - Lift both outer segments
        self.lift.move_back_up()
        self.lift.move_front_up()
        # 2 - Turn Robot 90°
        self.rotation.go_to_degree(90)

    
