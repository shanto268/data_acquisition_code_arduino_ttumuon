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

   nch=5;
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

   for(int i=0; i<6; i++) {
     adcthreshold[i]=100;
   }
}

void loop() {

  bx=bx+1;
  byte bx32=bx%32;
  byte bxNow=bx32
  for (int i=0; i<nch; i++) {
     adcpipe[bx32][i]=analogRead(adcpins[i])>>2;
  }

  // check the signals in n time slices before 
  byte tsBegin=bxNow32+15;   // .(+32) now, (31) now-1, (30) now-2, etc. 
  byte tsEnd=tsBegin+2;       // . (+2) -1,0,1  (+3) -1, 0, 1, 2, etc.

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
