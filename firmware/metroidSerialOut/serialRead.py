#!/usr/bin/python
import serial
import os
#import datetime
import time

s = serial.Serial("/dev/ttyUSB0", 9600) 
f = open("sensorData.txt", "w")
while True:
        x = s.read()
        #print(x)  
	#timestampData = str(datetime.datetime.now()) + ',' + str(x) + '\n'
	timestampData = int(time.time()) + ',' + str(x) + '\n'
        f.write(str(timestampData))
        f.flush()
        os.fsync(f)
f.close()
