import serial
#from Tkinter import *
#import tkMessageBox

port = "/dev/ttyUSB0"
ser = serial.Serial(port,9600)
value = 0


while 1:
    value = ser.read();
    #line = ser.readline();
    print value
    if value == "x":
#        tkMessageBox.showwarning("BLAH", "BLAH\n")
        exit()
    else:
        continue

