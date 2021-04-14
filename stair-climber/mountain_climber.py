import motors
import sensors


class MountainClimber:
    ultra_sonic = sensors.UltraSonic()
    buttons = sensors.Buttons()

    midMotor = motors.MidMotor()
    frontMotor = motors.FrontMotor()
    backMotor = motors.BackMotor()

    rotation = motors.StepperMotor()
    lift = motors.LiftMotor()

    videoStream = VideoStream()
    objectDetector = ObjectDetector()
    detectedPictogram = None

    def wait_for_start(self):
        self.buttons.wait_for_startbutton()

    def search_identify_pictogram(self):
        # Start Video Stream
        videoStream.start()

        # Look for Object for x seconds
        rotationDegrees = 0
        while detectedPictogram is None: 
            detectedPictogram = objectDetector.analyzeVideo(videoStream, 5)

            # If no Object found, turn by x Degrees. If Object found, return to starting Position
            if detectedPictogram is None: 
                rotationDegrees += 30
                rotation.go_to_degree(rotationDegrees)
            else:
                rotation.go_to_reference()

        # Stop the Video Stream
        videoStream.stop()


    def drive_to_stairs(self):
        # are we able to just drive straight or does the robot have to dodge the flag or alter his path otherwise
        # is this possible with the UltraSonic sensors?

        # drive forward
        frontMotor.accelerate() # can i set the speed somewhere? 
        distance_threshhold = 15 # idk what to put here, what value does get_distance give me?

        # noop while robot is far from stairs
        while ultra_sonic.get_distance1() > distance_threshhold:
            pass

        # Closer than threshhold
        frontMotor.stop()

        # maybe drive a little further to make sure we are touching the stairs?

    def climb_stairs(self):
        numberOfStairs = 5 

        for i in range(numberOfStairs + 1):
            self.__climb_one_stair()

    def __climb_one_stair(self):
        # Check if path is blocked

        # Move to side 

        
