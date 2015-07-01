# protocol source: http://protocol-jura.do.am/index/protocol_to_coffeemaker/0-7

import sys
import serial
import time
import struct
import binascii

# encode a byte to jura-encoding
# Information only in bit 2 and 5, all other bits are 1
# 4 UART bytes are one real byte:
# MSB.....LSB
# UART byte 33221100
# bit 52525252

# 76543210
# 11x11x11
# 11011011

# TODO
def decodequad(bin):
    return (bin[0] & 0x20) << 2 | (bin[0] & 0x04) << 6 | (bin[1] & 0x20) | (bin[1] & 0x04) << 2 | (bin[2] & 0x20) >> 2 | (bin[2] & 0x04) | (bin[3] & 0x20) >> 6 | (bin[3] & 0x04) >> 2

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
    return struct.pack("I", bs)

v = bytearray()
for c in "A":
    v.extend(encodebyte(c))

print ' '.join(format(x, 'b') for x in v)

c = decodequad(v)
print repr(c)
print chr(c)

#print repr(c, 'hex')
#print " .. check: {0:b}".format(encoded)
#binascii.hexlify(encoded)

cmdstr = "RE:31\r\n"
# cmdstr = "AN:02\r\n"

try:
    serialport = serial.Serial('/dev/ttyAMA0', 9600)
    serialport.open()
except:
    print "Geen serial port naar machine hepniedoenie"
    sys.exit()

# write machine code

print "Jura Hacking - sending 0x" + binascii.hexlify(cmdstr)

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
