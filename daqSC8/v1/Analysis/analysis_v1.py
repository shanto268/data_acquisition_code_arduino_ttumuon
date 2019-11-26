import numpy as np
import matplotlib.pyplot as plt   
n=0
n8=0
n9=0
Xadc8=np.zeros(200000) # number in function defined by (# collected by adc8)*(# of events in counter from "read_serial.py")
WTadc8=np.zeros(200000)
Xadc9=np.zeros(2000000) # number in function defined by (# collected by adc9)*(# of events in counter from "read_serial.py")
WTadc9=np.zeros(2000000) 
n8=0
n9=0
nevents=0
s8=np.zeros(200000)
t8=np.zeros(200000)
s9=np.zeros(200000)
t9=np.zeros(200000)
#  read x, y values lini-by-line from file
with open('/Users/ttumuon/muonSC8/daqSC8/v1/dataFiles/Run5_10kEvents_NLG.txt') as f:
   for line in f:          
       print line
       val=np.array([])   # val[0] will hold x and val[1] y.
       n=0;
       x8=np.zeros(4)
       x9=np.zeros(30)
       adc8=np.zeros(4)
       adc9=np.zeros(30)
       for number in line.split():
          # print n,"  ",number
          if n>3 and n<8:
              k=n-4
              x8[k]=float(k)
              adc8[k]=float(number)
              Xadc8[n8]=x8[k]
              WTadc8[n8]=adc8[k]
              n8=n8+1
          if n>12 and n<43:
              k=n-13
              x9[k]=float(k)
              adc9[k]=float(number)
              Xadc9[n9]=x9[k]
              WTadc9[n9]=adc9[k]
              n9=n9+1
          n=n+1
       print "x8=",x8
       print "adc8=",adc8
       print "x9=",x9
       print "adc9=",adc9
       #
       # find signal
       t8[nevents]=1.0
       s8[nevents]=adc8[1]
       for i in np.arange(0,30,1):
           if adc9[i]>32.0:
              t9[nevents]=i
              s9[nevents]=adc9[i]
              break
       nevents=nevents+1
# plot Worker 8 histogram
fig1=plt.figure(1)
xmin=0.0
xmax=4.0
dx=1.0
kwargs = dict(histtype='stepfilled', alpha=0.3, bins=np.arange(xmin,xmax+dx,dx))
plt.hist(Xadc8[0:n8], weights=WTadc8[0:n8], label='gaussian $\mu$=5.0, $\sigma$=1.0', **kwargs)
# plot Worker 9 histogram
fig2=plt.figure(2)
xmin=0.0
xmax=30.0
dx=1.0
kwargs = dict(histtype='stepfilled', alpha=0.3, bins=np.arange(xmin,xmax+dx,dx))
plt.hist(Xadc9[0:n9], weights=WTadc9[0:n9], label='gaussian $\mu$=5.0, $\sigma$=1.0', **kwargs)
# plot Worker 8 signal amplitude vs # of events
fig3=plt.figure(3)
xmin=0.0
xmax=200.0
dx=1.0
kwargs = dict(histtype='stepfilled', alpha=0.3, bins=np.arange(xmin,xmax+dx,dx))
plt.hist(s8[0:nevents], label='gaussian $\mu$=5.0, $\sigma$=1.0', **kwargs)
# plot Worker 9 signal amplitude vs # of events
fig4=plt.figure(4)
xmin=0.0
xmax=200.0
dx=1.0
kwargs = dict(histtype='stepfilled', alpha=0.3, bins=np.arange(xmin,xmax+dx,dx))
plt.hist(s9[0:nevents], log=True, label='gaussian $\mu$=5.0, $\sigma$=1.0', **kwargs)
# 2D plot of Worker 8(x) vs Worker 9(y) correlation between signal amplitude
fig5=plt.figure(5)
xbins=np.arange(0.0,200.0,10.0)
ybins=np.arange(0.0,200.0,10.0)
plt.hist2d(s8[0:nevents],s9[0:nevents], bins=[xbins,ybins], cmap='Blues')
cb = plt.colorbar()
cb.set_label('counts in bin')
# plot of timeslice for Worker 9
fig6=plt.figure(6)
xmin=0.0
xmax=30.0
dx=1.0
kwargs = dict(histtype='stepfilled', alpha=0.3, bins=np.arange(xmin,xmax+dx,dx))
plt.hist(t9[0:nevents], label='gaussian $\mu$=5.0, $\sigma$=1.0', **kwargs)
fig1.savefig('fig1_hist_1')
fig2.savefig('fig2_hist_2')
fig3.savefig('fig3_hist_3')
fig4.savefig('fig4_hist_4')
fig5.savefig('fig5_hist2D_5')
fig6.savefig('fig6_hist_6')
plt.show()

