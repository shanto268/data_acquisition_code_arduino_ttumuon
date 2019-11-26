// worker

#include <Wire.h>

int adcpin = 0;
int adcval = 0;
int wait = 1000;
byte trig = 0;
byte bxTrig=0;
int  adcThreshold=40;
byte param[10]; // threshold message

int adc[256];
byte bx = 230;
byte bxpick = bx - 3;
byte adcout[10];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(8);
  Wire.setClock(400000);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);


  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  
  // uncomment as required
  
//  ADCSRA |= bit (ADPS0);                               //   2  
//  ADCSRA |= bit (ADPS1);                               //   4  
//  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8  
  ADCSRA |= bit (ADPS2);                               //  16 
//  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32 
//  ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64 
//  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("trig " + (String)trig );
  if (int(trig) > 0) {
    // delay(5);
    return;
  }

  // unsigned long t0usec = micros();
  // unsigned long t1=millis();
  adcval = analogRead(adcpin);
  adc[bx] = adcval;
  bxTrig=bx;
  bx++;
  //    the threshold in Jan was 50
  if (adcval > adcThreshold) {
    trig = 1;
    // . read more time slices...
    for (int k=0; k<4; k++) {
       adc[bx] = analogRead(adcpin);
       bx++;
    }
  } // end of if (adcval > adcThreshold)
    
}  // end of loop

void requestEvent() {
  byte bx2a = bxTrig - 3 ;
  adcout[0] = trig;
  adcout[1] = bxTrig;
  adcout[2] = adcThreshold;

  for (int i=0; i<6; i++) {
    int k=i+3;
    adcout[k] = adc[bx2a] >> 2; // 2 bits shift, i.e. divided by 4.
    bx2a=bx2a+1;
  }
  //  sending 9 bytes.
  Wire.write(adcout, 9);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  int k = 0;
  
  while (Wire.available()) { // loop through all but the last
     param[k] = Wire.read(); // receive byte as a character
     k++;
     trig=0;
     adcThreshold=param[0];
  }
}
