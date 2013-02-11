/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2011.
THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
OR OTHER SIMILAR COSTS.
*********************************************************/

/********************************************************
 IMPORTANT : This Example is created for the Arduino 1.0 Software IDE
********************************************************/

#include <SMARTGPU.h>     //include the SMARTGPU library!

SMARTGPU lcd;             //create our object called LCD

#define orange   0xFC0F
#define brown    0xBBCA
#define ligBlue  0x96DD

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop
 
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
    lcd.drawCircle(35,120,35,GREEN,FILL);                                                              //draw a circle
    lcd.drawCircle(35,120,35,BLACK,UNFILL);                                                            //draw a circle 
    //draw right tree
    lcd.drawRectangle(270,167,283,218,brown,FILL);                                                     //draw a rectangle
    lcd.drawRectangle(270,167,283,218,BLACK,UNFILL);                                                   //draw a rectangle       
    lcd.drawCircle(277,134,35,GREEN,FILL);                                                             //draw a circle
    lcd.drawCircle(277,134,35,BLACK,UNFILL);                                                           //draw a circle  
    
    //draw grass
    lcd.drawLine(5,218,314,218,GREEN);                                                                 //draw a line    
    
    //loop forever
    while(1);
}
