void setup() {
  blink(13,5);
  delay(3000);
  blink(13,5);
  while (!Serial);
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
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
  //Serial.print("loop: \n");
  digitalWrite(11, HIGH);
  delay(300);
  digitalWrite(11, LOW);
  delay(500);
   
  digitalWrite(10, HIGH);
  delay(5000);
  digitalWrite(10, LOW);
  //delay(300);
  
  delay (3000);
}

void timeIt(){
  Serial.print("interrupt: ");
  Serial.println(millis());
}
