import unittest

from mountain_climber import MountainClimber


class UartTestCase(unittest.TestCase):
    def test_uart(self):
        climber = MountainClimber()
        response = climber.led.set_green(100)
        self.assertEqual(response, [54, 0, 100, 54, 0, 100, 10])


if __name__ == '__main__':
    unittest.main()
