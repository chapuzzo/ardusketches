void setup() {
  Serial.begin(115200);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
}

void loop() {
  Serial.print("pin 2:");
  Serial.println(digitalRead(2));
  Serial.print("pin 3:");
  Serial.println(digitalRead(3));
  Serial.print("pin 4:");
  Serial.println(digitalRead(4));
  delay(1000);
}
