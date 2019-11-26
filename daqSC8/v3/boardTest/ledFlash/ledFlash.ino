int ledPin=9;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);  
  delay(2000);
}
