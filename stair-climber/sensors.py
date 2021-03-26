from uart import Uart


class UltraSonic:
    uart = Uart()
    distanceCmd = bytes([])  # change

    def get_distance1(self):
        self.uart.write_uart_cmd(self.distanceCmd)

    def get_distance2(self):
        self.uart.write_uart_cmd(self.distanceCmd)


class Button:
    uart = Uart()
    pushCmd = bytes([])  # change

    def is_btn1_pushed(self):
        self.uart.write_uart_cmd(self.pushCmd)

    def is_btn2_pushed(self):
        self.uart.write_uart_cmd(self.pushCmd)
