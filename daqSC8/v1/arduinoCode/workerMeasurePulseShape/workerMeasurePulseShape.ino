// worker

#include <Wire.h>

int adcpin = 0;
int adcval = 0;
int wait = 2000;
byte trig = 0;

int adc[320];
byte bx = 230;
byte adcout[256];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  
  // uncomment as required
  
//  ADCSRA |= bit (ADPS0);                               //   2  
//  ADCSRA |= bit (ADPS1);                               //   4  
//  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8  
//  ADCSRA |= bit (ADPS2);                               //  16 
//  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32 
//  ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64 
  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128

}

void loop() {

  unsigned long t0usec = micros();
  // unsigned long t1=millis();
  adcval = analogRead(adcpin);
  adc[bx] = adcval;
  bx++;
  byte bxtest=bx-100;
  // Serial.println((String)bx+"   "+adcval+"   "+bxtest);
  if (adcval > 50) {
    trig = 1;
    byte tbx=bx-10;
    for (byte i=0; i<10; i++) {
      adcout[i]=adc[tbx];
      tbx++;
    }
    adcout[tbx]=adc[bx];
    tbx++;
    for (byte i=0; i<100; i++) {
    // . read more times...
      adc[bx] = analogRead(adcpin);
      bx++;
      adcout[tbx]=adc[bx];
      tbx++;
    }

    unsigned long dt = micros() - t0usec;

    // Serial.write(adcout, 50);
    Serial.println((String)adcout[0]+"  "+adcout[1]+"  "+adcout[2]+"  ");
    
    //Serial.println((String)adcvaladcval + "   " + dt + "  bx=" + bx + "  "
    //              + adc[bx2a] + " " + adc[bx2b] + " " + adc[bx2c] + " " + adc[bx2d]
    //              + " adc300 " + adc[300] + " " + adc[301]+ " " + adc[302]);
    // delay(wait);
  } // end of if (adcval > 50)
  delay(wait);
}
