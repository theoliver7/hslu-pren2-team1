# DC Motor 1
class MidMotor:
    def __init__(self, uart):
        self.uart = uart

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
    def __init__(self, uart):
        self.uart = uart

    def accelerate_forward(self, speed):
        cmd = bytes([9, 255, speed, 9, 255, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    def accelerate_backwards(self, speed):
        cmd = bytes([11, 0, speed, 11, 0, speed, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)


class StepperMotor:
    def __init__(self, uart):
        self.uart = uart

    # Mittleres Segment ist angehoben, degree in Bezug zum Referenzpunk
    def go_to_degree_inair(self, degree):
        degree_byte = int(degree / 1.8)
        cmd = bytes([21, 0, degree_byte, 21, 0, degree_byte, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Mittleres Segment ist am boden, degree in Bezug zum Referenzpunk
    def go_to_degree_onground(self, degree):
        degree_byte = int(degree / 1.8)
        cmd = bytes([22, 0, degree_byte, 22, 0, degree_byte, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Anfahrt der Referenzmarke, mittleres Segment am Boden
    def go_to_reference_onground(self):
        cmd = bytes([23, 180, 180, 23, 180, 180, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Anfahrt der Referenzmarke, mittleres Segment ist angehoben
    def go_to_reference_inair(self):
        cmd = bytes([24, 180, 180, 24, 180, 180, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)


class LiftMotor:
    def __init__(self, uart):
        self.uart = uart

    # Fahrtposition, hebe mittleres Segment leicht ab
    def driveMode_middleUp(self):
        cmd = bytes([27, 0, 0, 27, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Fahrtposition, setze mittleres Segment auf den Boden
    def driveMode_middleDown(self): 
        cmd = bytes([28, 0, 0, 28, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Setzte beide äusseren Achsen auf den Boden
    def lower_outer_axes(self):
        cmd = bytes([29, 0, 0, 29, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Drehposition, äussere Segmente leicht angehoben
    def rotationMode(self): 
        cmd = bytes([30, 0, 0, 30, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)

    # Steigt eine Treppenstufe hoch, Roboter muss vor einer Stufe sein
    def climb_stair(self): 
        cmd = bytes([50, 0, 0, 50, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        # Check for valid response
        return list(cmd) == list(response)
