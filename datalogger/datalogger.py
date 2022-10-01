import serial
from struct import *
import json
ser = serial.Serial('/dev/cu.usbmodem14101', 9600)
ser.flushInput()

while True:
    ser_bytes = ser.read(14)
    payload = unpack('fffh', ser_bytes)
    print(payload)

    with open('data.json') as outfile:
        #outfile.write()
        data = json.load(outfile)
        data['data'].append({
            "sensor_1": payload[0],
            "sensor_2": payload[1],
            "sensor_3": payload[2],
            "count": payload[3]
        })

    with open('data.json', 'w') as outfile:
        #json.dumps(data, outfile)
        outfile.write(json.dumps(data, sort_keys=True, indent=4))
        print(json.dumps(data, sort_keys=True, indent=4))
