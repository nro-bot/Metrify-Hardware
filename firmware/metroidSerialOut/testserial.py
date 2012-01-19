#!/usr/bin/python
import serial
#from Tkinter import *
#import tkMessageBox

port = "/dev/ttyUSB0"
ser = serial.Serial(port,9600)
value = 0


while 1:
    value = str(ser.readline())
    value.split()
    #line = ser.readline();
    if value is not None and len(value) > 0:
    	print value
#       tkMessageBox.showwarning("BLAH", "BLAH\n")
    else:
        continue


