void setup() {
  blink(13,5);
  delay(3000);
  blink(13,5);
  while (!Serial);
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  attachInterrupt(0,timeIt,CHANGE);
  Serial.println("comenzamos la medicion");
}

void blink(int pin, int times){
  pinMode(pin,OUTPUT);
  while(times--){
    digitalWrite(pin, HIGH);
    delay(150);
    digitalWrite(pin,LOW);
    delay(150);
  }
}

void loop() {
  Serial.print("loop: \n");
  digitalWrite(10, HIGH);
  Serial.println(digitalRead(2));
  delay(300);
  digitalWrite(10, LOW);
  delay(300);
  Serial.println(digitalRead(2));
  Serial.print("fin: \n");
}

void timeIt(){
  Serial.print("interrupt: ");
  Serial.println(millis());
}
