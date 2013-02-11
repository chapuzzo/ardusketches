#include <digitalWriteFast.h>
// ITDB02_Touch_QuickDraw (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a quick demo of how to use the library.
//
// This program requires the ITDB02_Graph library (8bit mode)
// or ITDB02_Graph16 (16bit mode).
//
// It is assumed that the ITDB02 module is connected to a
// ITDB02 Shield, a ITDB02 Mega Shield or that you know how 
// to change the pin numbers in the setup.
//
extern uint8_t BigFont[];
// Remember to change the next line if you are using as 16bit module!
#include <UTFT.h>
#include <ITDB02_Touch.h>

// Uncomment the next two lines for the ITDB02 Shield
UTFT        myGLCD(ITDB28,A5,A4,A3,A2);
ITDB02_Touch  myTouch(A1,A3,A0,8,9);

// Uncomment the next two lines for the ITDB02 Mega Shield
//ITDB02        myGLCD(38,39,40,41);   // Remember to add ASPECT_16x9 if you are using an ITDB02-3.2WC!
//ITDB02_Touch  myTouch(6,5,4,3,2);
int x,y;
char str[20];

void setup()
{
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myGLCD.setColor(0, 255, 0);

  myTouch.InitTouch(PORTRAIT);
  myTouch.setPrecision(PREC_LOW);
  
  //Serial.begin(9600);
}

void loop()
{
  int last_x=0, last_y=0;
  
    while (myTouch.dataAvailable() == true)
    {
      myTouch.read();
      //myGLCD.print("       ",x,y);
      //x=myTouch.getX();
      //y=myTouch.getY();
      //if (myTouch.getX() == x && myTouch.getY() == y)
      myGLCD.setColor(255, 0, 0);
      if(last_x == 0)
      {
        myGLCD.drawPixel(myTouch.getX(), myTouch.getY());
      }
      else
      {
        myGLCD.drawLine(last_x, last_y, myTouch.getX(), myTouch.getY()) ;
      }
      last_x = myTouch.getX();
      last_y = myTouch.getY();
      
      //myGLCD.fillCircle (x,y,3);
      
      sprintf(str,"   %d,%d   ",last_x,last_y);
      
      myGLCD.print(str,CENTER,300);
      myGLCD.setColor(0, 255, 0);
      //Serial.println(str);
      //myGLCD.setColor(random()*255,random()*255,random()*255);
    }
}

