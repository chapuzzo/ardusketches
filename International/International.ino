/*  PS2Keyboard library, International Keyboard Layout Example
    http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html

    keyboard.begin() accepts an optional 3rd parameter to
    configure the PS2 keyboard layout.  Uncomment the line for
    your keyboard.  If it doesn't exist, you can create it in
    PS2Keyboard.cpp and email paul@pjrc.com to have it included
    in future versions of this library.
*/
   
#include <PS2Keyboard.h>

const int VccPin = 10;
const int GndPin = 16;
const int IRQpin = A1;
const int DataPin = A0;


PS2Keyboard keyboard;

void setup() {
  pinMode(GndPin, OUTPUT);
  pinMode(VccPin, OUTPUT);
  digitalWrite(GndPin, HIGH);
  digitalWrite(VccPin, LOW);
  keyboard.begin(DataPin, IRQpin, PS2Keymap_US);
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_German);
  Serial.begin(9600);
  Serial.println("International Keyboard Test:");
}

void loop() {
  if (keyboard.available()) {
    char c = keyboard.read();
    Serial.print(c);
  }
}
