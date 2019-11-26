//
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
   Wire.begin();
   Wire.setClock(400000);
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.requestFrom(8,7);

  byte adcin[10];
  byte n=0;
  // Serial.print("\n");
  while (Wire.available()) { // slave may send less than requested
    byte c = Wire.read(); // receive a byte as character
    adcin[n]=c;
    n++;
    // Serial.print(c,DEC);         // print the character
    // Serial.print("\n");
  }
  if(adcin[0]>0) {
  Serial.println((String)adcin[0]+" "+adcin[1]+"       "+adcin[2]+" "+
  adcin[3]+" "+adcin[4]+" "+adcin[5]+"       "+adcin[6]+"  n="+n);
  delay(2000);
  }
}

