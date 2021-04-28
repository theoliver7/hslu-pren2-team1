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

    error = bytes([0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA])

    def write_uart_cmd(self, message):
        # TODO: figure out when to open and close USB
        self.ser.open()
        print('# bytes sent: '+str(self.ser.write(message)))
        response = self.ser.read(10)  # TODO: should only be 7 -> tinyk issue
        print(response)
        if response == self.error:
            print("error response from tiny") #TODO: retry?
        self.ser.close()
        return response


