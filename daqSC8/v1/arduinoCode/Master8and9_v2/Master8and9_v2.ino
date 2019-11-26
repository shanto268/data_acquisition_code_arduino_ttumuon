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

  byte y0 = 50; // param[0] -> Bxshift   default 13
  byte y1 = 8;  // param[1] -> extract adcval from pipeline every n-ts.
  Wire.beginTransmission(9); // transmit to device #8
  Wire.write(y0);              // sends one byte
  Wire.write(y1);              // sends one byte
  Wire.endTransmission();    // stop transmitting

   x = 40; // Threshold on trigger
   Wire.beginTransmission(8); // transmit to device #8
   Wire.write(x);              // sends one byte
   Wire.endTransmission();    // stop transmitting

  unsigned long t0usec = micros();      // t0
  Wire.requestFrom(8,9);                // id 8, requested bytes 9.
  unsigned long t1usec = micros();      // t1

  

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
    delay(1);   // delay 1 msec
    unsigned long t2usec = micros();       // t2
    Wire.requestFrom(9, 32);
    unsigned long t3usec = micros();       // t3

    byte adc2[256];
    byte k = 0;

    while (Wire.available()) {      // slave may send less than requested
      byte c = Wire.read();         // receive a byte as character
      adc2[k] = c;
      k++;
    }
    
    unsigned long t4usec = micros();       // t4
    int dt1=t1usec-t0usec;
    int dt2=t2usec-t1usec;
    int dt3=t3usec-t2usec;
    int dt4=t4usec-t3usec;
    int dt4a=t4usec-t0usec;
    byte  datatype=1;
    Serial.println((String)datatype+" "+adcin[0] + "  " + adcin[1] + "  " + adcin[2] + "  " +
                   adcin[3] + "  " + adcin[4] + "  " + adcin[5] + "  " + adcin[6] + "  " + adcin[7]+ "  " + adcin[8]
                   + "  n=" + n + " adc2  " + adc2[0] + " " + adc2[1] + "       " + adc2[2] + " " +
                   adc2[3] + " " + adc2[4] + " " + adc2[5] + " " + adc2[6] + " " + adc2[7] + " " + adc2[8] + " " +
                   adc2[9] + " " + adc2[10] + " " + adc2[11] + " " + adc2[12] + " " + adc2[13] + " " + adc2[14] + " " +
                   adc2[15] + " " + adc2[16] + " " + adc2[17] + " " + adc2[18]  + " " + adc2[19] + " " + adc2[20] + " " + adc2[21]
                   + " " + adc2[22] + " " + adc2[23] + " " + adc2[24]  + " " + adc2[25] + " " + adc2[26] + " " + adc2[27]
                   + " " + adc2[28] + " " + adc2[29] + " " + adc2[30]  + " " + adc2[31] + " " + " k = " + k 
                   + " "+dt1+ " "+dt2+ " "+dt3+ " "+dt4+ " "+dt4a);

    unsigned long t5usec = micros();       // t5
    long dt5=t5usec-t4usec;

    x = 255;
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    
    unsigned long t6usec = micros();       // t6
    int dt6=t6usec-t5usec;
    datatype=2;
    //Serial.println((String)datatype+"  "+dt1+"  "+dt2+"  "+dt3+"  "+dt4+"  "+dt5+"  "+dt6);
    unsigned long t7usec = micros();       // t7
    long dt7=t7usec-t6usec;
    datatype=3;
    //Serial.println((String)datatype+"  "+dt7);

    // delay(1000);
  }

}
