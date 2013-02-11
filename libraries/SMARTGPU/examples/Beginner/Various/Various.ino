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


char message[]="Hello World";


void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop
    delay(1000);                                                                                     //wait some time 
    lcd.drawLine(50,50,150,200,WHITE);                                                               //draw a line
    delay(1000);
    lcd.drawRectangle(10,10,200,180,RED,UNFILL);                                                     //draw a rectangle
    delay(1000);
    lcd.drawCircle(160,120,50,GREEN,UNFILL);                                                         //draw a circle
    delay(1000);
    lcd.drawTriangle(15,15,200,210,180,70,BLUE,UNFILL);                                              //draw a triangle
    delay(1000);                                                                                 
    lcd.string(10,10,300,220,YELLOW,FONT3,TRANS,"This is the string test for SMARTGPU lcd320x240");  //write a string on the screen
    delay(1000);    
    lcd.string(10,60,300,220,GREEN,FONT3,TRANS,message);                                            //write the string previously created (char message[]="Hello World";)
    delay(1000);
    lcd.putLetter(100,100,MAGENTA,FONT3,TRANS,'E');                                                  //write a single letter 'E'
    delay(1000);
    lcd.putPixel(300,200,CYAN);                                                                      //draw a pixel
    delay(3000);
    lcd.imageSD(0,0,"hydra320");                                                                     //call the image "hydra320.bmp" previously stored on the micro SD card
    delay(1000);    
    lcd.stringSD(5,50,300,230,MAGENTA,FONT3,TRANS,BEGINNING,ALLCONTENTS,"text1");                    //call the text file "text1.txt" previously stored on the micro SD card
    delay(1000);   
    lcd.drawRectangle(10,10,200,180,RED,FILL);                                                       //draw a rectangle
    delay(1000);
    lcd.drawCircle(160,120,50,GREEN,FILL);                                                           //draw a circle
    delay(1000);
    lcd.drawTriangle(15,15,200,210,180,70,BLUE,FILL);                                                //draw a triangle 
    delay(3000);
    lcd.erase();                                                                                     //erase screen
}
