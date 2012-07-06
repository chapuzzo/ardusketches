void setup() {
 Serial.begin(9600);
}

void loop() {
//  Serial.println(millis());
//  delay(200);
Serial.println(analogRead(0));
delay(1000);
  
}
