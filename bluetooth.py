import serial
import time
import datetime
import mysql.connector
import pymysql

print("Start")

bluetooth = serial.Serial('COM10', 9600, timeout = 1)

cnx = pymysql.connect(host="clover.cclls6i3ttha.us-east-2.rds.amazonaws.com",port=3306,user="clover", password="clover1234", db="clover")
cursor = cnx.cursor()

add_tracker = ("INSERT INTO plant_monitor "
               "(moisture_level, light_intensity, date_time) "
               "VALUES (%s, %s, %s)")

time.sleep(3)

print("Connected")
while(1):
    now = datetime.datetime.now()
    input_data = bluetooth.readline()

    if(len(input_data) != 0):
        data = input_data.decode()
        print(data)
        words = data.split()
        print(words)
        data_tracker = (words[0], words[1], str(now))
        cursor.execute(add_tracker, data_tracker)
        emp_no = cursor.lastrowid
        cnx.commit()
    else:
        print("empty")

bluetooth.close()
cursot.close()
cnx.close()

print("done")