import serial
from struct import *
import json


import serial.tools.list_ports
comlist = serial.tools.list_ports.comports()
connected = []
print(chr(27) + "[2J")
print("Ports availables:")
for index, element in enumerate(comlist):
    connected.append(element.device)
    print("{}: {}".format(index, element.device))
print("-----------------")

port_selected = input("Choose de port serial: ")
port = comlist[int(port_selected)].device

while True:
    ser = serial.Serial(port, 9600)
    ser.flushInput()
    ser_bytes = ser.read(14)
    print(ser_bytes)
