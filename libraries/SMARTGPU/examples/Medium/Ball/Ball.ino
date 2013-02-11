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

// defines for balls
#define radiusBall1 10     //ball1 size
#define colourBall1 RED    //ball1 colour

//variables used by move ball method
int speedBall1=3; //ball1 moving speed - amount of pixels that ball move each time
int dirx1=1;      //xball1 initial positive direction
int diry1=-1;     //yball1 initial negative direction
int xBall1=300;   //x initial position of ball1
int yBall1=100;   //y initial position of ball1

/***************************************************/
//Function that updates the current position of the ball1
void moveBall1(){
   lcd.drawCircle(xBall1,yBall1,radiusBall1,BLACK,FILL);       // Erase previous ball position
   xBall1+=(dirx1*speedBall1);                                 // Calculate new x coordinate for ball1 
   yBall1+=(diry1*speedBall1);                                 // Calculate new y coordinate for ball1  
   lcd.drawCircle(xBall1,yBall1,radiusBall1,colourBall1,FILL); // Draw new ball position
   if((xBall1+speedBall1+radiusBall1)>318 | (xBall1-speedBall1-radiusBall1)<=1){           // if ball reaches the left or right corner, we invert moving direction 
    dirx1= dirx1*(-1);                                         // Invert the moving direction by multiplying by -1
   }
   if((yBall1+speedBall1+radiusBall1)>238 | (yBall1-speedBall1-radiusBall1)<=1){           // if ball reaches the top or bottom corner, we invert moving direction 
    diry1= diry1*(-1);                                         // Invert the moving direction by multiplying by -1
   }                       
}

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop 
  lcd.baudChange(1000000); //set a fast baud! for fast drawing
  lcd.drawRectangle(0,0,319,239,YELLOW,UNFILL); //draw corners
  
  while(1){             // Loop forever
    moveBall1();        // move ball1
    delay(15);          // wait a little
  }
}
