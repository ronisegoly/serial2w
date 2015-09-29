from time import sleep
import serial
ser = serial.Serial('/dev/ttyACM0', 9600) # Establish the connection on a specific port
sleep(4)
counter = 32 # Below 32 everything in ASCII is gibberish
while True:
     #get new command from redis
     command="dummy"	
     ser.write(command) # Convert the decimal number to ASCII then send it to the Arduino
     print ser.readline() # Read the newest output from the Arduino
     sleep(1)
