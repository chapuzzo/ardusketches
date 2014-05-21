// LCD5110_Bitmap (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use bitmaps.
// You can also see how to use invert().
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Basic.h>

LCD5110 myGLCD(13,11,10,8,12);

extern uint8_t arduino_logo[];
extern uint8_t oshw_logo[];
extern uint8_t SmallFont[];


void setup()
{
  int i;
  //myGLCD.InitLCD();
  pinMode(6,OUTPUT);
  analogWrite(6,200);
  //myGLCD.setFont(SmallFont);
  /*for (i=0; i<1024; i++){
    analogWrite(6,i);
    delay(10);
  }
    for (i=0; i<1024; i++){
    analogWrite(6,1024-i);
    delay(10);
  }*/
 blink(13,10);
}

void blink(int pin, int times){
  pinMode(pin, OUTPUT);
  while (times--){
   digitalWrite(pin,HIGH);
   delay(20);
   digitalWrite(pin,LOW);
  }
}

void loop()
{
  /*myGLCD.drawBitmap(0, 0, arduino_logo, 84, 48);
  delay(4000);
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }*/
  //myGLCD.print("hola. hola", CENTER, CENTER);
  
  int i=0;
  for (i=0; i<120; i++){
    //myGLCD.setContrast(i);
    delay(50);
    blink(13,5);
  }
  
  /*delay(4000);

  myGLCD.clrScr();
  myGLCD.drawBitmap(14, 0, oshw_logo, 56, 48);
  delay(4000);
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }
  delay(4000);*/
}
