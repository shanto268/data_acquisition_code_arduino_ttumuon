import numpy as np
import ROOT
from ROOT import TFile
from ROOT import TH1F, TCanvas, TGraph, TH2F
from ROOT import gROOT,gStyle

n=0
n8=0
n9=0

Xadc8=np.zeros(70000) # number in function defined by (# collected by adc8)*(# of events in counter from "read_serial.py")
WTadc8=np.zeros(70000)
Xadc9=np.zeros(320000) # number in function defined by (# collected by adc9)*(# of events in counter from "read_serial.py")
WTadc9=np.zeros(320000)

n8=0
n9=0

nevents=0
s8=np.zeros(30000)
t8=np.zeros(30000)
s9=np.zeros(30000)
t9=np.zeros(30000)

# Data file path
path = 'Run5_10kEvents_NLG.txt'
rtf = TFile('hist.root', 'RECREATE')

h1 = TH1F("test1","Node 8",4,0,4)
h2 = TH1F("test2","Node 9",30,0,30)
h3 = TH1F("test3","Signal8 vs N",200,0,200)
h4 = TH1F("test4","Signal9 vs N",200,0,200)
h5 = TH2F("test5","Correlations",10,0,200,10,0,200)

#  read x, y values line-by-line from file
with open(path) as f:
    for line in f:
       #sk print line
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
                h1.Fill(x8[k],adc8[k])
            if n>12 and n<43:
                k=n-13
                x9[k]=float(k)
                adc9[k]=float(number)
                Xadc9[n9]=x9[k]
                WTadc9[n9]=adc9[k]
                n9=n9+1
                h2.Fill(x9[k],adc9[k])
            n=n+1
       #sk print "x8=",x8
       #sk print "adc8=",adc8
       #sk print "x9=",x9
       #sk print "adc9=",adc9
       #
       # find signal
        t8[nevents]=1.0
        s8[nevents]=adc8[1]
        h3.Fill(adc8[1])
        for i in np.arange(0,30,1):
            if adc9[i]>32.0:
                t9[nevents]=i
                s9[nevents]=adc9[i]
                h4.Fill(adc9[i])
                h5.Fill(adc8[1],adc9[i])
                break
        #if s9[nevents] < 1.0:
            #print "nevents ",nevents,"  ",adc9
        nevents=nevents+1

h1.Draw()
h2.Draw()
h3.Draw()
h4.Draw()
h5.Draw('colz')

h1.Write()
h2.Write()
h3.Write()
h4.Write()
h5.Write()

rtf.Close()
