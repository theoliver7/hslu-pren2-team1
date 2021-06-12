import serial
import numpy

# TODO singleton
class Uart:
    ser = serial.Serial()
    ser.port = '/dev/ttyACM0'  # depends on host for raspi /dev/ttyACM0
    ser.baudrate = 57600
    ser.bytesize = serial.EIGHTBITS
    ser.parity = serial.PARITY_NONE
    ser.stopbits = serial.STOPBITS_ONE

    error = bytes([170, 170, 170, 170, 170, 170, 10])

    def __init__(self):
        self.ser.open()

    def write_uart_cmd(self, message):
        print('# bytes sent: '+str(self.ser.write(message)))
        response = self.ser.read(7)
        print("uart response: "+str(list(response)))

        if response == self.error:
            print("error response from tiny") #TODO: retry?
            response = self.ser.read(7)
            print("uart retry response: " + str(list(response)))
        return response


