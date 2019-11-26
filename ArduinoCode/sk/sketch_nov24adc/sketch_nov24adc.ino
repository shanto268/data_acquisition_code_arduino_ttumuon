
int ledPin=13;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adc0=analogRead(0);
  if(adc0>0) {
      digitalWrite(ledPin, HIGH);
      int adcin[30];
      for(int i=0;i<20;i++) {
        adcin[i]=analogRead(0);
      }
      Serial.println((String)" "+adc0+"  "+adcin[0]
      +"  "+adcin[1]+"  "+adcin[2]+"  "+adcin[3]
      +"  "+adcin[4]+"  "+adcin[5]+"  "+adcin[6]
      +"  "+adcin[7]+"  "+adcin[8]+"  "+adcin[9]
      +"  "+adcin[10]+"  "+adcin[11]+"  "+adcin[12]
      +"  "+adcin[13]+"  "+adcin[14]+"  "+adcin[15]
      +"  "+adcin[16]+"  "+adcin[17]+"  "+adcin[18]       
      );
      delay(100);
      digitalWrite(ledPin, LOW);    
  }
}
