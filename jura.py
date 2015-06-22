import sys
import serial
import time

def encode(str):
    # Information only in bit 2 and 5, all other bits allways 1!
    # 4 UART bytes are one real byte:
    # MSB.....LSB
    # UART byte 33221100
    # bit 52525252
    return str

serialport = serial.Serial('/dev/ttyAMA0', 9600)
serialport.open()

try:
    while true:
        response = serialport.readline()
        print response
except KeyboardInterrupt:
    serialport.close()
