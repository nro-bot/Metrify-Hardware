#!/usr/bin/python
import serial
import os
#import datetime
import time

s = serial.Serial("/dev/ttyUSB0", 9600) 
f = open("sensorData.txt", "w")
buttonState = 0
while True:
        x = s.readline().split()
	if x != buttonState:
        #print(x)  
	#timestampData = str(datetime.datetime.now()) + ',' + str(x) + '\n'
		buttonState = x
		timestampData = str(int(time.time())) + ',' + ''.join(x) + '\n'
		f.write(timestampData)
	#if len(timestampData) > 0:
	#	f.write(timestampData)
        f.flush()
        os.fsync(f)
f.close()
