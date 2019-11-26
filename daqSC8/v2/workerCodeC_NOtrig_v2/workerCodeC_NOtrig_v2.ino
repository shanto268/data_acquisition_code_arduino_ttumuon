// worker 2

#include <Wire.h>

int adcpin = 0;
int adcval = 0;
int wait = 1000;
byte trig = 0;
byte param[10]; //  0 bxShift

int adc[256];
byte bx = 230;
byte bxpick = bx - 3;
byte adcout[256];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(9);
  Wire.setClock(400000);
  Wire.onRequest(requestEvent);
  
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
  byte bxx = bx - param[0] ;
  trig=2;
  adcout[0] = trig;
  adcout[1] = bxx;
  adcout[2] = param[0];
  
  for (int i = 3; i < 32 ; i++) {
    adcout[i] = adc[bxx]>>2;
    bxx++;
  }
  Wire.write(adcout, 32);
}
