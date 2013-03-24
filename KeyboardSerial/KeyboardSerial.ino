void setup() {
  // open the serial port:
  while (!Serial);
  Serial.begin(9600);
  // initialize control over the keyboard:
  Keyboard.begin();
  //for (int i=0; i<10; i++){
  //Keyboard.write('@');
  //delay(200);
  //}
}

void loop() {
  // check for incoming serial data:
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    // Type the df2ASCII value from what you received:
    Keyboard.write(inChar);
  }  
}

