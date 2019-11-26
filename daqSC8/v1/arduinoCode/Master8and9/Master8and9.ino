#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(9600);
}

byte x = 0;

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long t0usec = micros();       // t0

  Wire.requestFrom(8, 7);                // time to request = ~200us

  unsigned long dt0 = micros() - t0usec; // time for request

  byte adcin[10];
  byte n = 0;
  // Serial.print("\n");
  while (Wire.available()) {      // slave may send less than requested
    byte c = Wire.read();         // receive a byte as character
    adcin[n] = c;
    // if (n > 3) break;
    n++;
    // Serial.print(c,DEC);       // print the character
    // Serial.print("\n");
  }


  //   triggered event...
  if (adcin[0] > 0) {
    unsigned long dt1 = micros() - t0usec;     // time to first signal

    Wire.requestFrom(9, 32);

    unsigned long dt2 = micros() - t0usec;

    byte adc2[256];
    byte k = 0;
    // Serial.print("\n");

    while (Wire.available()) {      // slave may send less than requested
      byte c = Wire.read();         // receive a byte as character
      adc2[k] = c;
      k++;
      //Serial.print(c, DEC);      // print the character
      //Serial.print("\n");
    }

    Serial.println((String)adcin[0] + " " + adcin[1] + "       " + adcin[2] + " " +
                   adcin[3] + " " + adcin[4] + " " + adcin[5] + "       " + adcin[6] + "  n=" + n +
                   " adc2  " + adc2[0] + " " + adc2[1] + "       " + adc2[2] + " " +
                   adc2[3] + " " + adc2[4] + " " + adc2[5] + " " + adc2[6] + " " + adc2[7] + " " + adc2[8] + " " +
                   adc2[9] + " " + adc2[10] + " " + adc2[11] + " " + adc2[12] + " " + adc2[13] + " " + adc2[14] + " " +
                   adc2[15] + " " + adc2[16] + " " + adc2[17] + " " + adc2[18]  + " " + adc2[19] + " " + adc2[20] + " " + adc2[21]
                   + " " + adc2[22] + " " + adc2[23] + " " + adc2[24]  + " " + adc2[25] + " " + adc2[26] + " " + adc2[27]
                   + " " + adc2[28] + " " + adc2[29] + " " + adc2[30]  + " " + adc2[31] + " " + " k = " + k );
    //for(int i=0;i<256;i++){
    // Serial.println((String)i + " adc is "+ adc2[i]);
    //  }
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write("x is");              // sends one byte
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    //Serial.println("end check");

    // delay(1000);
  }

}
