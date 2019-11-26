import numpy as np
import matplotlib.pyplot as plt   
import sys

n=0
n8=0

Xadc8=np.zeros(70000) # number in function defined by (# collected by adc8)*(# of events in counter from "read_serial.py")
WTadc8=np.zeros(70000)

nevents=0
s8=np.zeros(30000)
t8=np.zeros(30000)

# Data file path
# path = '/Users/kfanta/Desktop/muonSC8/data/Run1_100Events.txt'
path = sys.argv[1]

#  read x, y values line-by-line from file
with open(path) as f:
   for line in f:          
       print line
       val=np.array([])   # val[0] will hold x and val[1] y.
       n=0;
       x8=np.zeros(30)
       adc8=np.zeros(30)

       for number in line.split():
          # print n,"  ",number
          if n>-1 and n<30:
              k=n
              x8[k]=float(k)
              adc8[k]=float(number)
              Xadc8[n8]=x8[k]
              WTadc8[n8]=adc8[k]
              n8=n8+1
          n=n+1
       print "x8=",x8
       print "adc8=",adc8
       #
       # find signal
       t8[nevents]=1.0
       s8[nevents]=adc8[1]
       nevents = nevents+1
# plot Worker 8 histogram
fig1=plt.figure(1)

xmin=0.0
xmax=30.0
dx=1.0
kwargs = dict(histtype='stepfilled', alpha=0.3, bins=np.arange(xmin,xmax+dx,dx))
plt.hist(Xadc8[0:n8], weights=WTadc8[0:n8], label='gaussian $\mu$=5.0, $\sigma$=1.0', **kwargs)
plt.xlabel('Timeslice')
plt.ylabel('ADC Counts')
plt.title('Node 8')

# plot Worker 8 signal amplitude vs # of events
fig2=plt.figure(2)
xmin=0.0
xmax=200.0
dx=1.0
kwargs = dict(histtype='stepfilled', alpha=0.3, bins=np.arange(xmin,xmax+dx,dx))
plt.hist(s8[0:nevents], label='gaussian $\mu$=5.0, $\sigma$=1.0', **kwargs)

plt.xlabel('Binned event fraction')
plt.ylabel('Signal Amplitude')
plt.title('Node 8')

fig1.savefig('fig1_hist_1')
fig2.savefig('fig2_hist_2')
plt.show()
