int ledPin=13;
int adcpin=0;
int adcval=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);  
  delay(2000);
  adcval=analogRead(adcpin);
  unsigned long dt = micros();
  Serial.println((String)adcval+" test  time="+dt);
}
