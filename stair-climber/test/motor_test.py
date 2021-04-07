import unittest

from motors import StepperMotor


class MotorTestCase(unittest.TestCase):

    def test_stepper_motor(self):
        stepper = StepperMotor()
        stepper.go_to_degree(90)
        self.assertEqual(True, True)


if __name__ == '__main__':
    unittest.main()
