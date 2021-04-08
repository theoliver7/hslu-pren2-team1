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

    def wait_for_start(self):
        self.buttons.wait_for_startbutton()

    def search_identify_pictogram(self):
        raise NotImplementedError

    def drive_to_stairs(self):
        raise NotImplementedError

    def climb_stairs(self):
        raise NotImplementedError

    def __climb_one_stair(self):

        raise NotImplementedError
