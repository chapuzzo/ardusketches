// UTFT_ViewFont (C)2014 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the included fonts.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>

const int triggerPin = 6;
const int echoPin = 7;

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT myGLCD(TFT01_22SP,9,8,12,11,10);

void setup()
{
  myGLCD.InitLCD();

  myGLCD.clrScr();

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 0);

  //myGLCD.print("0123456789", CENTER, CENTER);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  myGLCD.setFont(BigFont);
  myGLCD.print("     ", CENTER, 120);

  int cm = microsecondsToCentimeters(duration);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(cm, CENTER, 120);

  //while(1) {};
  delay(100);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}