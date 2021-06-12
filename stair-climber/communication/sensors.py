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
        return response

    def set_blue(self, intensity):
        cmd = bytes([57, 0, intensity, 57, 0, intensity, 10])
        response = self.uart.write_uart_cmd(cmd)


class UltraSonic:
    def __init__(self, uart):
        self.uart = uart

    def get_distance1(self):
        cmd = bytes([45, 0, 0, 45, 0, 0, 10])
        response = list(self.uart.write_uart_cmd(cmd))
        print(response)
        # TODO can't calc like that bit shift 16 bit number stretched over 2 byte
        shifted = response[1] * 2 ** 8
        distance_value = shifted + response[2]
        print("Distance" + str(distance_value))
        return distance_value

    def get_distance2(self):
        cmd = bytes([48, 0, 0, 48, 0, 0, 10])
        response = self.uart.write_uart_cmd(cmd)
        print(response)
        # TODO can't calc like that bit shift 16 bit number stretched over 2 byte
        shifted = response[1] * 2 ** 8
        distance_value = shifted + response[2]
        print("Distance" + str(distance_value))
        return distance_value


class Buttons:
    # Buttons
    start_btn = Button(0)
    whatever_btn = Button(5)
    leftFront_btn = Button(26, pull_up=None, active_state=False)
    leftBack_btn = Button(13, pull_up=None, active_state=False)
    rightFront_btn = Button(19, pull_up=None, active_state=True)
    rightBack_btn = Button(6, pull_up=None, active_state=True)

    def __init__(self):
        self.start_btn.when_pressed = lambda: print("Hello, Button start!")
        self.whatever_btn.when_pressed = lambda: print("Hello, WhateverButton start!")
        self.leftFront_btn.when_pressed = lambda: print("Hello, Button left front!")
        self.leftBack_btn.when_pressed = lambda: print("Hello, left back!")
        self.rightFront_btn.when_pressed = lambda: print("Hello, right front!")
        self.rightBack_btn.when_pressed = lambda: print("Hello, right back")

    def wait_for_startbutton(self):
        self.start_btn.wait_for_press()
        print("Button pressed let's go")
