import unittest

from climber import Climber


class UartTestCase(unittest.TestCase):
    def test_uart(self):
        climber = Climber()
        response = climber.led.set_green(100)
        self.assertEqual(response, [54, 0, 100, 54, 0, 100, 10])


if __name__ == '__main__':
    unittest.main()
