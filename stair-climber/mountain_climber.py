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

    def search_identify_pictogram(self):
        # 1 - Start Video Stream
        videoStream.start()

        # 2 - Look for Object for x seconds
        rotationDegrees = 0
        while detectedPictogram is None: 
            detectedPictogram = objectDetector.analyzeVideo(videoStream, 5)

            # 3 - If no Object found, turn by x Degrees. If Object found, return to starting Position
            if detectedPictogram is None: 
                rotationDegrees += 30
                rotation.go_to_degree(rotationDegrees)
            else:
                rotation.go_to_reference()

        # Stop the Video Stream
        videoStream.stop()


    def drive_to_stairs(self):
        raise NotImplementedError

    def climb_stairs(self):
        raise NotImplementedError

    def __climb_one_stair(self):
        raise NotImplementedError
