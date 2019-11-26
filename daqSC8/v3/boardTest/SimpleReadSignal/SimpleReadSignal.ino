// worker

// #include <Wire.h>


byte bx=0;
byte trigbx=0;
int adcpipe[256];
int adcout[100];
int adcpin = 0 ;

signed long timeLast =0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  //   ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear ps ... deafult digitization is ~100ms, here we can change speed of digitization
  //   ADCSRA |= bit (ADPS1);  // set prescaler to 4
  //   ADCSRA |= bit (ADPS1);  // set prescaler to 8
  //   ADCSRA |= bit (ADPS2);  // set prescaler to 16
}

void loop() {
  
  int adc = analogRead(adcpin);     
  adcpipe[bx]=adc;
  bx=bx+1;
  

  if(adc>15) {
     unsigned long timeNow = micros();
     unsigned long dt=timeNow-timeLast;
     timeLast=timeNow;
     trigbx=bx;

     // read more ADC values...
     for(int i = 0; i<20; i++){
        adc = analogRead(adcpin);
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
  
}
