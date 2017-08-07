import serial

ser = serial.Serial('/dev/ttyUSB0',9600)

while 1: 
        x=ser.readline()
        x = str(ser.readline())
         
        print x
       #time.sleep(1)--delay
