from uart import Uart


class SegmentMotor:
    uart = Uart()
    startcmd = bytes([])  # change
    stopcmd = bytes([])  # change

    def start_motor(self):
        self.uart.write_uart_cmd(self.startcmd)

    def stop_motor(self):
        self.uart.write_uart_cmd(self.stopcmd)


class FakeMotor:
    uart = Uart()
    startcmd = bytes([0x2E, 0x00, 0xFF, 0x2E, 0x00, 0xFF, 0x0A])  # change
    stopcmd = bytes([0x2E, 0x00, 0xFF, 0x2E, 0x00, 0xFF, 0x0A])  # change

    def start_motor(self):
        self.uart.write_uart_cmd(self.startcmd)

    def stop_motor(self):
        self.uart.write_uart_cmd(self.stopcmd)
