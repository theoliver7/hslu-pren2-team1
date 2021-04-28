from uart import Uart

# DC Motor 1
class MidMotor:
    uart = Uart()

    def accelerate_forward(self, speed):
        cmd = bytes([3, 255, speed, 3, 255, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    def accelerate_backwards(self, speed):
        cmd = bytes([5, 255, speed, 5, 255, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)


# DC Motor 2 & DC Motor 3
class OuterMotors: 
    uart = Uart()

    def accelerate_forward(self, speed):
        cmd = bytes([9, 255, speed, 9, 255, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    def accelerate_backwards(self, speed):
        cmd = bytes([10, 255, speed, 10, 255, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)


class StepperMotor:
    uart = Uart()

    def go_to_degree(self, degree):
        degree_byte: int = int(degree / 1.8)
        degree_hex = hex(degree_byte)
        cmd = bytes([21, 0, degree_hex, 21, 0, degree_hex, 10]) 
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    def go_to_reference(self):
        cmd = bytes([22, 180, 180, 22, 180, 180, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)


class LiftMotor:
    uart = Uart()

    def move_front_up(self, speed):
        cmd = bytes([24, 0, speed, 24, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    def move_front_down(self, speed):
        cmd = bytes([27, 0, speed, 27, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)
        
    # TODO - We dont need this? Was in definition file, but move_front_up(0) does the same thing
    def stop_front(self):
        cmd = bytes([28, 0, 0, 28, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    def move_back_up(self, speed):
        cmd = bytes([30, 0, speed, 30, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    def move_back_down(self, speed):
        cmd = bytes([33, 0, speed, 33, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Lift robot
    def move_both_up(self, speed): 
        # TODO: Byte-Values not yet defined - check if correct
        cmd = bytes([36, 0, speed, 36, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Lower robot
    def move_both_down(self, speed):
        # TODO: Byte-Values not yet defined - check if correct
        cmd = bytes([39, 0, speed, 39, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Climb stair
    def move_frontDown_BackUp(self, speed):
        # TODO: Byte-Values not yet defined - check if correct 
        cmd = bytes([42, 0, speed, 45, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)