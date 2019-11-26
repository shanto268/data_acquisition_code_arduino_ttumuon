// worker

// #include <Wire.h>

int nch=6;
int adcpins[6];
int adcthreshold[6];
int adcpipe[4][6];

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

   adcthreshold[0]=0;   //  in byte 
   adcthreshold[1]=0;
   adcthreshold[2]=0;
   adcthreshold[3]=0;
   adcthreshold[4]=0;
   adcthreshold[5]=0;

   for(int i=0; i<6; i++) {
     adcthreshold[i]=adcthreshold[i]*4;
   }
}

void loop() {

  bx=bx+1;
  int k2=bx%4 ;
  int k0=(k2+2)%4;
  int k1=(k2+3)%4;
  for (int i=0; i<nch; i++) {
     // for(int j=0;j<5;j++) {int preread=analogRead(adcpins[i]);} // read a few times
     adcpipe[k2][i]=analogRead(adcpins[i]);
     if(nout<noutmax) {
     // if(adcpipe[k1][i]>adcthreshold[i] && adcpipe[k0][i]<adcpipe[k1][i] && adcpipe[k1][i]>adcpipe[k2][i]) {
        unsigned long timeNow = millis();
        outdata[nout]=adcpins[i];
        outdata[nout+1]=timeNow;
        outdata[nout+2]=adcpipe[k0][i]>>2;
        outdata[nout+3]=adcpipe[k0][i]>>2;  
        nout=nout+4; 
     // }
     }
  }

  if(nout>3) {
    Serial.println((String) nout+"    "+outdata[0]+" "+outdata[1]+" "+outdata[2]+" "+outdata[3]
    +"    "+outdata[4]+" "+outdata[5]+" "+outdata[6]+" "+outdata[7]
    +"    "+outdata[8]+" "+outdata[9]+" "+outdata[10]+" "+outdata[11]
    +"    "+outdata[12]+" "+outdata[13]+" "+outdata[14]+" "+outdata[15]
    +"    "+outdata[16]+" "+outdata[17]+" "+outdata[18]+" "+outdata[19]
    +"    "+outdata[20]+" "+outdata[21]+" "+outdata[22]+" "+outdata[23]
    +"    "+outdata[24]+" "+outdata[25]+" "+outdata[26]+" "+outdata[27]);
    nout=0;
    for (int i=0; i<28; i++) {outdata[i]=0;}
    delay(2000);
  }
  
  /*int adc = analogRead(0);     
  adcpipe[bx]=adc;
  bx=bx+1;

  if(adc>90) {
     unsigned long timeNow = micros();
     unsigned long dt=timeNow-timeLast;
     timeLast=timeNow;
     trigbx=bx;

     // read more ADC values...
     for(int i = 0; i<20; i++){
        adc = analogRead(0);
        adcpipe[bx]=adc;
        bx=bx+1;   
     }
     // .  extract ADC values from pipeline.
     for(int k=0; k<20; k++) {
        byte ts=trigbx+k-4;
        adcout[k]=adcpipe[ts];
     }

    Serial.println((String)"dt= "+dt+"  adc= "+adcout[0] + "  " + adcout[1] + "  " + adcout[2] + "  " + adcout[3]
           + "  " + adcout[4] + "  " + adcout[5] + "  " + adcout[6] + "  " + adcout[7] + "  "
           +        adcout[8] + "  " + adcout[9] + "  " + adcout[10] + "  " + adcout[11] + "  " + adcout[12]
           + "  " + adcout[13] + "  " + adcout[14] + "  " + adcout[15] + "  " + adcout[16] + "  " + adcout[17]
           + "  " + adcout[18] + "  " + adcout[19] + "  " + adcout[20]);

    delay(1000);
            
  } //    if(adc>15) {
  */
}
