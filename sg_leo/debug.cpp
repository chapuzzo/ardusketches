#include "Arduino.h"
#include <SMARTGPU.h>

extern SMARTGPU lcd;

void rejilla(uint8_t dx, uint8_t dy){
  uint16_t x,y;

  for (x=0; x<WIDTH; x+=dx)
    lcd.drawLine(x,0,x,HEIGHT,WHITE);
  for (y=0; y<HEIGHT; y+=dy)
    lcd.drawLine(0,y,WIDTH,y,WHITE);

  lcd.drawLine(x-1,0,x-1,HEIGHT,WHITE);
  lcd.drawLine(0,y-1,WIDTH,y-1,WHITE);
}

void drawHouse(){
#define orange   0xFCC0
#define brown    0xBBCA
#define ligBlue  0x96DD

  //draw the house
  lcd.drawRectangle(78,134,212,217,orange,FILL);                                                     //draw a rectangle
  lcd.drawRectangle(78,134,212,217,BLACK,UNFILL);                                                    //draw a rectangle   
  lcd.drawTriangle(75,133,216,133,146,63,RED,FILL);                                                  //draw a triangle     
  lcd.drawTriangle(75,133,216,133,146,63,BLACK,UNFILL);                                              //draw a triangle     
  lcd.drawRectangle(136,167,170,217,brown,FILL);                                                     //draw a rectangle
  lcd.drawRectangle(136,167,170,217,BLACK,UNFILL);                                                   //draw a rectangle
  lcd.drawCircle(106,160,15,ligBlue,FILL);                                                           //draw a circle
  lcd.drawCircle(106,160,15,BLACK,UNFILL);                                                           //draw a circle    
  lcd.drawCircle(195,187,10,ligBlue,FILL);                                                           //draw a circle
  lcd.drawCircle(195,187,10,BLACK,UNFILL);                                                           //draw a circle

  //draw left tree
  lcd.drawRectangle(25,157,45,218,brown,FILL);                                                       //draw a rectangle
  lcd.drawRectangle(25,157,45,218,BLACK,UNFILL);                                                     //draw a rectangle       
  lcd.drawCircle(35,122,35,GREEN,FILL);                                                              //draw a circle
  lcd.drawCircle(35,122,35,BLACK,UNFILL);                                                            //draw a circle 
  //draw right tree
  lcd.drawRectangle(270,167,283,218,brown,FILL);                                                     //draw a rectangle
  lcd.drawRectangle(270,167,283,218,BLACK,UNFILL);                                                   //draw a rectangle       
  lcd.drawCircle(277,134,35,GREEN,FILL);                                                             //draw a circle
  lcd.drawCircle(277,134,35,BLACK,UNFILL);                                                           //draw a circle  

  //draw grass
  lcd.drawLine(5,218,314,218,GREEN);                                                                 //draw a line    
}
