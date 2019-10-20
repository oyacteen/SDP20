import serial
import time

print("Start")

bluetooth = serial.Serial('COM7', 9600, timeout = 1)
time.sleep(3)

print("Connected")
while(1):

    input_data = bluetooth.readline()
    if(len(input_data) != 0):
        print(input_data.decode())
        time.sleep(.1)
    else:
        print("empty")

bluetooth.close()

print("done")