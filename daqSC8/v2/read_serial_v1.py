import serial
import time
import glob
import sys
import signal
from datetime import datetime
from multiprocessing import process

def signal_handler(signal, frame):
   print '\n You pressed Ctrl+C! \n'
   ComPort.close()
   file.close()
   sys.exit(0)


#if __name__ '__main__':

print 'Welcome to TTU MuonSC8 serial reading!'

print 'Taking data...'
print 'Press ctrlc to terminate the process'
print '  '

signal.signal(signal.SIGINT, signal_handler)

# fname='/home/pi/sk/datafile_test.txt'
# fname='/Users/kunori/work/datafile_test.txt'
fname='datafile_test.txt'

# signal.signal(signal.SIGINT, signal_handler)

# The port name may be found in Arduino's Serial Monitor under Tools.
# ComPort = serial.Serial('/dev/ttyACM0')
# ComPort = serial.Serial('/dev/cu.usbmodem14410')
ComPort = serial.Serial('/dev/cu.usbmodem141101')
# ComPort = serial.Serial('/dev/cu.wchusbserial14410')

ComPort.baudrate = 9600
ComPort.bytesize = 8
ComPort.parity   = 'N'    # no parity
ComPort.stopbits = 1

file = open(fname, "w", 0)

counter = 0
while True:
   data = ComPort.readline()
   s = str(datetime.now())+"  "+data
   file.write(s)
   counter +=1
   print 'counter=',counter
   print s
   if counter>10000:
       break

ComPort.close()
file.close()

