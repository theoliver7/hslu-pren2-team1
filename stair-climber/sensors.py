from uart import Uart
from gpiozero import Button

# TODO: Are the cmd correct? Normaly bit 1 & bit 4 are the same (see motors), but not here, maybe it was forgotten
class LED:
    uart = Uart()

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
    uart = Uart()
    distanceCmd = bytes([])  # change

    def get_distance1(self):
        cmd = bytes([45, 15, 15, 45, 15, 15, 10])
        response = self.uart.write_uart_cmd(self.distanceCmd)

        distanceValue = response[1] + response[2]
        return distanceValue

    def get_distance2(self):
        cmd = bytes([48, 15, 15, 48, 15, 15, 10])
        response = self.uart.write_uart_cmd(self.distanceCmd)

        distanceValue = response[1] + response[2]
        return distanceValue


class Buttons:
    # Buttons
    start_btn = Button(26)
    leftFront_btn = Button(19)
    leftBack_btn = Button(13)
    rightFront_btn = Button(6)
    rightBack_btn = Button(0)

    # do we need to define this? -> Button for when axis touches the ground
    axis_btn = Button() 

    def is_rightFront_pressed(self):
        if rightFront_btn.is_pressed: 
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def is_rightBack_pressed(self):
        if rightBack_btn.is_pressed: 
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def is_leftFront_pressed(self):
        if leftFront_btn.is_pressed: 
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def is_leftBack_pressed(self):
        if leftBack_btn.is_pressed: 
            print("ressed")
            return True
        else:
            print("not pressed")
            return False

    def wait_for_startbutton(self):
        self.start_btn.wait_for_press()
        print("Button pressed let's go")
