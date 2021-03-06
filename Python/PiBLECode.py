from bluepy import btle
import time
import datetime
import mysql.connector
import pymysql
import os
from concurrent import futures
from subprocess import check_output

global addr_var
global delegate_global
global perif_global

addr_var = ['78:db:2f:14:01:fe']

cnx = pymysql.connect(host="clover.cclls6i3ttha.us-east-2.rds.amazonaws.com",port=3306,user="clover", password="clover1234", db="clover")
cursor = cnx.cursor()

add_tracker = ("INSERT INTO plant_monitor "
                "(moisture_level, light_intensity, date_time) "
                "VALUES (%s, %s, %s)")

class MyDelegate(btle.DefaultDelegate):

    def __init__(self,params):
        btle.DefaultDelegate.__init__(self)

    def handleNotification(self,cHandle,data):
        global addr_var
        global delegate_global

        for ii in range(len(addr_var)):
            if delegate_global[ii]==self:
                try:
                    data_decoded = data.decode("utf-8")
                    #perif_global[ii].writeCharacteristic(cHandle,struct.pack("b",55))
                    print("Address: "+addr_var[ii])
                    print(data_decoded)
                    try:
                        sendDataToServer(data)
                    except:
                        pass

                    return
                except:                    
                    pass
                try:
                    data_decoded = data.decode('utf-8')
                   # perif_global[ii].writeCharacteristic(cHandle,struct.pack("b",55))
                    print("Address: "+addr_var[ii])
                    print(data_decoded)
                    try:
                        sendDataToServer(data)
                    except:
                        pass
                    return
                except:
                    return

def sendDataToServer(data):
    now = datetime.datetime.now()
    dataStr = data.decode("utf-8")
    dataArr = dataStr.split()
    moistVal = dataArr[0]
    distVal = dataArr[1]
    data_tracker = [moistVal, distVal, str(now)]
    cursor.execute(add_tracker, data_tracker)
    emp_no = cursor.lastrowid
    cnx.commit()
    print("Data has been sent to server")
    print(data_tracker)
    return

def perif_loop(perif,indx):
    while True:
        try:
            print("waiting for notifications...")
            if perif.waitForNotifications(1.0):
                continue
        except:
            try:
                perif.unpair
                perif.disconnect()
                print("disconnecting from "+perif.addr)
                return
            except:
                return
            print("disconnecting perif: "+perif.addr+", index: "+str(indx))
            reestablish_connection(perif,perif.addr,indx)
            
delegate_global = []
perif_global = []
[delegate_global.append(0) for ii in range(len(addr_var))]
[perif_global.append(0) for ii in range(len(addr_var))]

def reestablish_connection(perif,addr,indx):
    while True:
        try:
            print("trying to reconnect with "+addr)
            perif.connect(addr)
            print("re-connected to "+addr+", index = "+str(indx))
            return
        except:
            continue

def establish_connection(addr):
    global delegate_global
    global perif_global
    global addr_var

    while True:
        try:
            for jj in range(len(addr_var)):
                if addr_var[jj]==addr:
                    print("Attempting to connect with "+addr+" at index: "+str(jj))
                    p = btle.Peripheral(addr)
                    perif_global[jj] = p
                    p_delegate = MyDelegate(addr)
                    delegate_global[jj] = p_delegate
                    p.setDelegate(p_delegate)
                    print("Connected to "+addr+" at index: "+str(jj))                    
                    perif_loop(p,jj)
        except:
            check_output("sudo hciconfig hci0 down",shell=True).decode()
            check_output("sudo hciconfig hci0 up",shell=True).decode()
            print("failed to connect to "+addr)
            
ex = futures.ProcessPoolExecutor(max_workers = os.cpu_count())
results = ex.map(establish_connection,addr_var)