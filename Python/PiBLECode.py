from bluepy import btle
import os
from concurrent import futures

global addr_var
global delegate_global
global perif_global

addr_var = ['78:DB:2F:14:01:FE']

class MyDelegate(btle.DefaultDelegate):

    def __init__(self,params):
        btle.DefaultDelegate.__init__(self)

    def handleNotification(self,cHandle,data):
        global addr_var
        global delegate_global

        for ii in range(len(addr_var)):
            if delegate_global[ii]==self:
                try:
                    # data_decoded = data.decode("utf-8")
                    perif_global[ii].writeCharacteristic(cHandle,struct.pack("b",55))
                    print("Address: "+addr_var[ii])
                    #print(data_decoded)
                    try:
                        sendDataToServer(data)
                    except:
                        pass

                    return
                except:                    
                    pass
                try:
                    data_decoded = data.decode('utf-8')
                    perif_global[ii].writeCharacteristic(cHandle,struct.pack("b",55))
                    print("Address: "+addr_var[ii])
                    print(data_decoded)
                    try:
                        sendDataToServer(data)
                    except:
                        pass
                    return
                except:
                    return

def perif_loop(perif,indx):
    while True:
        try:
            if perif.waitForNotifications(1.0):
                print("waiting for notifications...")
                continue
        except:
            try:
                perif.disconnect()
            except:
                pass
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
                    p.withDelegate(p_delegate)
                    print("Connected to "+addr+" at index: "+str(jj))                    
                    perif_loop(p,jj)
        except:
            print("failed to connect to "+addr)
            continue

def sendDataToServer(data):
    global moisture
    global distance

    cnx = pymysql.connect(host="clover.cclls6i3ttha.us-east-2.rds.amazonaws.com",port=3306,user="clover", password="clover1234", db="clover")
    cursor = cnx.cursor()

    add_tracker = ("INSERT INTO plant_monitor "
                "(moisture_level, light_intensity, date_time) "
                "VALUES (%s, %s, %s)")
    now = datetime.datetime.now()
    dataStr = data.decode("utf-8")
    dataArr = data.split()
    moistVal = dataArr[0]
    distVal = dataArr[1]
    data_tracker = (moistVal, distVal, str(now))
    cursor.execute(add_tracker, data_tracker)
    emp_no = cursor.lastrowid
    cnx.commit()
    print("Data has been sent to server")
    return
