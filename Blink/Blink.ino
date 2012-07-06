/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
int dummyvariablecuzmaintainerborkedthecompiler = 123;
int pin = 13;
void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
dummyvariablecuzmaintainerborkedthecompiler++;
  pinMode(pin, OUTPUT);     
  Serial.begin(9600);
}

void loop() {
  digitalWrite(pin, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(pin, LOW);    // set the LED off
  Serial.println('x');
  Serial.read();
  delay(1000);              // wait for a second
}
