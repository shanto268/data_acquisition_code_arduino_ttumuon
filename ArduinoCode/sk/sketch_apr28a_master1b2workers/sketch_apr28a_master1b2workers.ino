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
    if(n>3) break;
    n++;
    // Serial.print(c,DEC);         // print the character
    // Serial.print("\n");
  }
  //   triggered event...
  if(adcin[0]>0) {
     Serial.println((String)adcin[0]+" "+adcin[1]+"       "+adcin[2]+" "+
     adcin[3]+" "+adcin[4]+" "+adcin[5]+"       "+adcin[6]+"  n="+n);

     Wire.requestFrom(9,7);
     byte adc2[10];  
     byte k=0;
     // Serial.print("\n");
     while (Wire.available()) { // slave may send less than requested
       byte c = Wire.read(); // receive a byte as character
       adc2[k]=c;
       k++;
         // Serial.print(c,DEC);         // print the character
         // Serial.print("\n");
     }
      Serial.println((String)"adc2  "+adc2[0]+" "+adc2[1]+"       "+adc2[2]+" "+
      adc2[3]+" "+adc2[4]+" "+adc2[5]+"       "+adc2[6]+"  n="+k);   
      delay(2000);
  }

}

