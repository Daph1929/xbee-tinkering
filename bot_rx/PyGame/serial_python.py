import serial

ser = serial.Serial('/dev/ttyACM0',115200)

while 1: 
        x=ser.readline()
        x = str(ser.readline())
         
        print x
        time.sleep(1)
