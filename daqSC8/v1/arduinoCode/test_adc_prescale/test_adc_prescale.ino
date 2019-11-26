int ledPin=13;
int adcpin=0;
int adcval=0;
int adcval2=0;
unsigned long t1;
unsigned long t2,dt2;
unsigned long t3,dt3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

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
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);  
  delay(2000);
  t1 = micros();
  adcval=analogRead(adcpin);
  t2 = micros();
  dt2=t2-t1;
  adcval2=analogRead(adcpin);
  t3 = micros();
  dt3=t3-t2;
  Serial.println((String)adcval+" . "+adcval2+" time= "+t1+
    "  dt= "+dt2+"   "+dt3);
  delay(1000);
}
