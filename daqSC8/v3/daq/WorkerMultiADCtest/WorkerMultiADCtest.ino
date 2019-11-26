// worker

// #include <Wire.h>

int nch=6;
int adcpins[6];
int adcthreshold[6];
int adcpipe[32][6];

int nout=0;
int noutmax=7*4;
byte bx=0;
byte outdata[32];

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

    ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  
//  ADCSRA |= bit (ADPS0);                               //   2  
//  ADCSRA |= bit (ADPS1);                               //   4  
//  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8  
  ADCSRA |= bit (ADPS2);                               //  16.  (20 micro sec)
//  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32 
//  ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64 
//  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128 (slowest)

   nch=6;
   adcpins[0]=0;
   adcpins[1]=1;
   adcpins[2]=2;
   adcpins[3]=3;
   adcpins[4]=6;
   adcpins[5]=7;

   adcthreshold[0]=0;
   adcthreshold[1]=0;
   adcthreshold[2]=0;
   adcthreshold[3]=0;
   adcthreshold[4]=0;
   adcthreshold[5]=0;

   for(int i=0; i<nch; i++) {
     adcthreshold[i]=70;
   }
}

void loop() {

  bx=bx+1;
  byte bx32=bx%32;
  byte bxTrig32=bx32;
  // read all channels and store adcval in the pipeline (length 32)
  int trig=0;
  for (int i=0; i<nch; i++) {
     adcpipe[bx32][i]=analogRead(adcpins[i])>>2;
     if(adcpipe[bx32][i]>adcthreshold[i]) {
        trig=1;
     }
  }

  if(trig>0) {
     // . read more ADC values to see the time structure of the signal
     for (int k=0; k<15; k++) {
        bx=bx+1;
        bx32=bx%32;
        for (int i=0; i<nch; i++) {
          adcpipe[bx32][i]=analogRead(adcpins[i])>>2;
        }
     }
     
           Serial.println((String)" ");
     for (int i=0; i<nch; i++) {
        byte tsBegin=bxTrig32+29;
        byte tsEnd=tsBegin+32;
        byte k=0;
        for (byte t=tsBegin; t<tsEnd; t++) {
          byte ts=t%32;
          outdata[k]=adcpipe[ts][i];
          k=k+1;
        }
        Serial.println((String)"ch "+i
       +"    "+outdata[0]+" "+outdata[1]+" "+outdata[2]+" "+outdata[3]
       +"  "+outdata[4]+" "+outdata[5]+" "+outdata[6]+" "+outdata[7]
       +"  "+outdata[8]+" "+outdata[9]+" "+outdata[10]+" "+outdata[11]
       +"  "+outdata[12]+" "+outdata[13]+" "+outdata[14]+" "+outdata[15]);
     } // end of loop over nchan.
     delay(2000);
  }  // end of  if(trig>0)

}
