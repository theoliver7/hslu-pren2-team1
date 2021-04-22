from uart import Uart


class MidMotor:
    uart = Uart()

    def accelerate(self, speed):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)

    def stop(self):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)


class FrontMotor:
    uart = Uart()

    def accelerate(self, speed):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)

    def stop(self):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)


class BackMotor:
    uart = Uart()

    def accelerate(self, speed):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)

    def stop(self):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)

# combined class for both outer motors so the can be controlled at the same time
class OuterMotors: 
    uart = Uart()

    def accelerate(self, speed):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)

    def stop(self):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])  # TODO Change
        self.uart.write_uart_cmd(cmd)


class StepperMotor:
    uart = Uart()

    def go_to_degree(self, degree):
        degree_byte: int = int(degree / 1.8)  # TODO ask if oke
        print(hex(degree_byte))
        degree_hex = hex(degree_byte)
        degree_cmd = bytes([0x15, 0x00, 0x00, 0x2E, 0x00, 0xFF, 0x0A])  # change
        degree_cmd[2] = degree_hex
        print(degree_cmd)
        self.uart.write_uart_cmd(degree_cmd)

    def go_to_reference(self):
        goto_cmd = bytes([0x16, 0xB4, 0xB4, 0x16, 0xB4, 0xB4, 0x0A])
        self.uart.write_uart_cmd(goto_cmd)


class LiftMotor:
    uart = Uart()

    def move_front_up(self):
        cmd = bytes([0x18, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0x0A])
        self.uart.write_uart_cmd(cmd)

    def move_front_down(self):
        cmd = bytes([0x1B, 0x00, 0x00, 0x1B, 0xFF, 0xFF, 0x0A])
        self.uart.write_uart_cmd(cmd)

    def move_back_up(self):
        cmd = bytes([0x1E, 0xFF, 0xFF, 0x1E, 0xFF, 0xFF, 0x0A])
        self.uart.write_uart_cmd(cmd)

    def move_back_down(self):
        cmd = bytes([0x21, 0x00, 0x00, 0x21, 0x00, 0x00, 0x0A])
        self.uart.write_uart_cmd(cmd)

    def move_both_up(self): 
        cmd = bytes([0x21, 0x00, 0x00, 0x21, 0x00, 0x00, 0x0A])
        self.uart.write_uart_cmd(cmd)

    def move_both_down(self):
        cmd = bytes([0x21, 0x00, 0x00, 0x21, 0x00, 0x00, 0x0A])
        self.uart.write_uart_cmd(cmd)

    # Needed for middle segment? Is this possible/ok ?
    def move_frontUp_BackDown(self): 
        cmd = bytes([0x21, 0x00, 0x00, 0x21, 0x00, 0x00, 0x0A])
        self.uart.write_uart_cmd(cmd)

    def move_frontDown_BackUp(self):
        cmd = bytes([0x21, 0x00, 0x00, 0x21, 0x00, 0x00, 0x0A])
        self.uart.write_uart_cmd(cmd)