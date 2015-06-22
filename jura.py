# protocol source: http://protocol-jura.do.am/index/protocol_to_coffeemaker/0-7

import sys
import serial
import time
import struct

# encode a byte to jura-encoding
# Information only in bit 2 and 5, all other bits are 1
# 4 UART bytes are one real byte:
# MSB.....LSB
# UART byte 33221100
# bit 52525252
def encodebyte(bin):
    bs = 0xDADADADA # template

    b = struct.unpack("B", bin)[0]

    bs |= ((b & 0x80) >> 2) << 24
    bs |= ((b & 0x40) >> 4) << 24
    bs |= ((b & 0x20)) << 16
    bs |= ((b & 0x10) >> 2) << 16
    bs |= ((b & 0x08) << 2) << 8
    bs |= ((b & 0x04)) << 8
    bs |= ((b & 0x02) << 4)
    bs |= ((b & 0x01) << 2)

    return chr(bs & 0xFF000000 >> 24) + chr(bs & 0x00FF0000 >> 16) + chr(bs & 0x0000FF00 >> 8) + chr(bs & 0x000000FF)

cmdstr = "RE:31\r\n"
# cmdstr = "AN:02\r\n"

serialport = serial.Serial('/dev/ttyAMA0', 9600)
serialport.open()

# write machine code

print "Jura Hacking nnngnggg - sending " + cmdstr

for c in cmdstr:
    ec = encodebyte(c)
    print ".. sending " + ec
    serialport.write(ec)
    time.sleep(8 / 1000) # 8ms break between bytegroups

# show results
try:
    print "Reading response: "
    while True:
        response = serialport.read()
        print hex(ord(response))
except KeyboardInterrupt:
    serialport.close()
