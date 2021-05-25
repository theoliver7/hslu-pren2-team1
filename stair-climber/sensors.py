from gpiozero import Button


# TODO: Are the cmd correct? Normaly bit 1 & bit 4 are the same (see motors), but not here, maybe it was forgotten
class LED:
    def __init__(self, uart):
        self.uart = uart
        self.set_green(0)
        self.set_red(0)
        self.set_blue(0)

    def set_red(self, intensity):
        cmd = bytes([51, 0, intensity, 51, 0, intensity, 10])
        response = self.uart.write_uart_cmd(cmd)

    def set_green(self, intensity):
        cmd = bytes([54, 0, intensity, 54, 0, intensity, 10])
        response = self.uart.write_uart_cmd(cmd)

    def set_blue(self, intensity):
        cmd = bytes([57, 0, intensity, 57, 0, intensity, 10])
        response = self.uart.write_uart_cmd(cmd)


class UltraSonic:
    def __init__(self, uart):
        self.uart = uart

    def get_distance1(self):
        cmd = bytes([45, 0, 0, 45, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        print(response)
        # TODO can't calc like that bit shift 16 bit number stretched over 2 byte
        distanceValue = response[1] + response[2]
        return distanceValue

    def get_distance2(self):
        cmd = bytes([48, 0, 0, 48, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        print(response)
        # TODO can't calc like that bit shift 16 bit number stretched over 2 byte
        distanceValue = response[1] + response[2]
        return distanceValue


class Buttons:
    # Buttons
    start_btn = Button(0)
    leftFront_btn = Button(26, active_state=False)
    leftBack_btn = Button(13, active_state=False)
    rightFront_btn = Button(19, active_state=False)
    rightBack_btn = Button(6, active_state=False)

    def __init__(self):
        self.start_btn.when_pressed = lambda: print("Hello, Button start!")
        self.leftFront_btn.when_pressed = lambda: print("Hello, Button left front!")
        self.leftBack_btn.when_pressed = lambda: print("Hello, left back!")
        self.rightFront_btn.when_pressed = lambda: print("Hello, right front!")
        self.rightBack_btn.when_pressed = lambda: print("Hello, right back")

    def is_rightFront_pressed(self):
        if self.rightFront_btn.is_pressed:
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def is_rightBack_pressed(self):
        if self.rightBack_btn.is_active:
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def is_leftFront_pressed(self):
        if self.leftFront_btn.is_pressed:
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def is_leftBack_pressed(self):
        if not self.leftBack_btn.is_active:
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def wait_for_startbutton(self):
        self.start_btn.wait_for_press()
        print("Button pressed let's go")
