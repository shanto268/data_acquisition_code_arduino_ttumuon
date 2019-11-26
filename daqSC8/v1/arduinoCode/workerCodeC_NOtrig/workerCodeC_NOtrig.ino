// worker 2

#include <Wire.h>

int adcpin = 0;
int adcval = 0;
int wait = 1000;
byte trig = 0;

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

  // ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear ps
  // ADCSRA |= bit (ADPS1);  // set prescaler to 4
  // ADCSRA |= bit (ADPS1);  // set prescaler to 8
  // ADCSRA |= bit (ADPS2);  // set prescaler to 16
}

void loop() {
  // put your main code here, to run repeatedly:
  //if (trig == 1) {
  //  delay(2000);
  //  return;
  //  }
  unsigned long t0usec = micros();
  // unsigned long t1=millis();
  adcval = analogRead(adcpin);
  adc[bx] = adcval;
  // adc[bx] = bx;
  bx++;
  unsigned long dt = micros() - t0usec;
  byte bx2a = bx - 4 + 256;
  byte bx2b = bx2a + 1;
  byte bx2c = bx2b + 1;
  byte bx2d = bx2c + 1;
  trig = 2;
  //Serial.println((String)adcval + "   " + dt + "  bx=" + bx + "  "
  //               + adc[bx2a] + " " + adc[bx2b] + " " + adc[bx2c] + " " + adc[bx2d]
  //               + " a1 " + adc[201] + "   adc202  " + adc[202]);
  //delay(wait);

}
void requestEvent() {
  byte bxx = bx - 15 + 256 ;
  //byte bx2b = bxx + 1;
  //byte bx2c = bx2b + 1;
  //byte bx2d = bx2c + 1;
  adcout[0] = trig;
  adcout[1] = bxx;
  //adcout[2] = adc[bxx] >> 1;
  //adcout[3] = adc[bx2b] >> 1;
  //adcout[4] = adc[bx2c] >> 1;
  //adcout[5] = adc[bx2d] >> 1;
  for (int i = 2; i < 256 ; i++) {
    adcout[i] = adc[bxx];
    bxx++;
  }
  //adcout[6] = adc[200];
  Wire.write(adcout, 32);
  trig = 0;
}
