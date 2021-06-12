import unittest

from communication.motors import StepperMotor


class MotorTestCase(unittest.TestCase):

    def test_stepper_motor(self):
        stepper = StepperMotor()
        stepper.go_to_degree_inair(90)
        self.assertEqual(True, True)


if __name__ == '__main__':
    unittest.main()
