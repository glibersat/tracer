from dxfgeom import read_entities, line_from_elist, find_entities
from serial import Serial
import struct
import binascii
import time

elist = read_entities("drawing.dxf")

line_indexes = find_entities('LINE', elist)

lines = []

for line_index in line_indexes:
    lines.append(line_from_elist(elist, line_index))

segments = [(line.x1, line.y1, line.x2, line.y2) for line in  lines]

serial = Serial("/dev/ttyACM0", 9600, timeout=None)

for segno, segment in enumerate(segments):
    print "--- segno %d" % segno
    for i in range(0, 4):
        val = segment[i]
        bytes = struct.pack("<f", val)  
        print val, len(bytes), binascii.hexlify(bytes)
        bytes_written = serial.write(bytes)
        assert(bytes_written==len(bytes))

    serial.flushOutput()

    time.sleep(1)

    print "~ waiting return"
    print serial.inWaiting()
    bytes = serial.read(1)
    print bytes
        
    # print serial.read(4)