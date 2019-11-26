// worker 2

#include <Wire.h>

int adcpin = 0;
int adcval = 0;
int wait = 1000;
byte trig = 0;
byte param[5]; //  [0]=bxShift

int adc[256];
byte bx = 230;
byte bxpick = bx - 3;
byte adcout[32];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(9);
  Wire.setClock(400000);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  
  // uncomment as required
  
//  ADCSRA |= bit (ADPS0);                               //   2  
//  ADCSRA |= bit (ADPS1);                               //   4  
//  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8  
//  ADCSRA |= bit (ADPS2);                               //  16 
//  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32 
//  ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64 
  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128 (slowest)

}

void loop() {
  // put your main code here, to run repeatedly:

  // unsigned long t0usec = micros();
  adcval = analogRead(adcpin);
  adc[bx] = adcval;
  bx++;

}
void requestEvent() {
  if(param[2]>0) {
    adc[bx]=0;
    bx++;
    int kmax=param[2];
    for (int k=0; k<kmax;k++) {
       adc[bx]=analogRead(adcpin); 
       bx++;   
    }
  }
  byte bxx = bx - param[0] ;
  trig=2;
  adcout[0] = trig;
  adcout[1] = bxx;
  adcout[2] = param[0];
  adcout[3] = param[1];
  adcout[4] = param[2];

  
  for (int i = 5; i < 32 ; i++) {
    adcout[i] = adc[bxx]>>2;
    // bxx++;
    bxx=bxx+param[1];
  }
  Wire.write(adcout, 32);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  byte k = 0;
  
  while (Wire.available()) { // loop through all but the last
     param[k] = Wire.read(); // receive byte as a character
     k++;
  }
}
