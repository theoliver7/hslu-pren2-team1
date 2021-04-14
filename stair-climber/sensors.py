from uart import Uart
from gpiozero import Button


class UltraSonic:
    uart = Uart()
    distanceCmd = bytes([])  # change

    def get_distance1(self):
        cmd = bytes([0x16, 0xB4, 0xB4, 0x16, 0xB4, 0xB4, 0x0A])
        response = self.uart.write_uart_cmd(self.distanceCmd)
        # TODO parse distance

    def get_distance2(self):
        cmd = bytes([0x16, 0xB4, 0xB4, 0x16, 0xB4, 0xB4, 0x0A])
        response = self.uart.write_uart_cmd(self.distanceCmd)
        # TODO parse distance


class Buttons:
    uart = Uart()
    start_btn = Button(2)  # TODO determine gpio pin config

    # TODO rename to proper side of the robot
    def is_btn1_pushed(self):
        cmd = bytes([0x28, 0x01, 0x01, 0x28, 0x01, 0x01, 0x0A])
        response = self.uart.write_uart_cmd(cmd)
        print('response byte' + response[2])
        if response == 255:
            print("pushed")
            return True
        elif response == 0:
            print("not pushed")
            return False

    # TODO rename to proper side of the robot
    def is_btn2_pushed(self):
        cmd = bytes([0x2D, 0x01, 0x01, 0x2D, 0x01, 0x01, 0x0A])
        response = self.uart.write_uart_cmd(cmd)
        print('response byte' + response[2])
        if response == 255:
            print("pushed")
            return True
        elif response == 0:
            print("not pushed")
            return False

    def wait_for_startbutton(self):
        self.start_btn.wait_for_press()
        print("Button pressed let's go")
