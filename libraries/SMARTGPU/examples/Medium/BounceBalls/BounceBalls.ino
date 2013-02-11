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
#define radiusBall1 15     //ball1 size
#define colourBall1 GREEN  //ball1 colour
#define radiusBall2 8      //ball2 size
#define colourBall2 YELLOW //ball2 colour
#define radiusBall3 11     //ball3 size
#define colourBall3 RED    //ball3 colour
#define radiusBall4 18     //ball4 size
#define colourBall4 BLUE   //ball4 colour

//variables used by move ball methods
int speedBall1=3; //ball1 moving speed - amount of pixels that ball move each time
int speedBall2=4; //ball2 moving speed - amount of pixels that ball move each time 
int speedBall3=8; //ball3 moving speed - amount of pixels that ball move each time 
int speedBall4=6; //ball4 moving speed - amount of pixels that ball move each time 
int dirx1=1;      //xball1 initial positive direction
int diry1=1;      //yball1 initial positive direction
int xBall1=300;   //x initial position of ball1
int yBall1=100;   //y initial position of ball1
int dirx2=-1;     //xball2 initial negative direction
int diry2=-1;     //yball2 initial negative direction
int xBall2=30;    //x initial position of ball2
int yBall2=80;    //y initial position of ball2
int dirx3=-1;     //xball3 initial negative direction
int diry3=1;      //yball3 initial negative direction
int xBall3=60;    //x initial position of ball3
int yBall3=15;    //y initial position of ball3
int dirx4=1;      //xball4 initial negative direction
int diry4=-1;     //yball4 initial negative direction
int xBall4=150;   //x initial position of ball4
int yBall4=80;    //y initial position of ball4

/***************************************************/
//Function that updates the current position of the ball1
void moveBall1(){
   lcd.drawCircle(xBall1,yBall1,radiusBall1,BLACK,UNFILL);       // Erase previous ball position
   xBall1+=(dirx1*speedBall1);                                   // Calculate new x coordinate for ball1 
   yBall1+=(diry1*speedBall1);                                   // Calculate new y coordinate for ball1  
   lcd.drawCircle(xBall1,yBall1,radiusBall1,colourBall1,UNFILL); // Draw new ball position
   if((xBall1+speedBall1+radiusBall1)>318 | (xBall1-speedBall1-radiusBall1)<=1){           // if ball reaches the left or right corner, we invert moving direction 
    dirx1= dirx1*(-1);                                         // Invert the moving direction by multiplying by -1
   }
   if((yBall1+speedBall1+radiusBall1)>238 | (yBall1-speedBall1-radiusBall1)<=1){           // if ball reaches the top or bottom corner, we invert moving direction 
    diry1= diry1*(-1);                                         // Invert the moving direction by multiplying by -1
   }                       
}

/***************************************************/
//Function that updates the current position of the ball2
void moveBall2(){                    
   lcd.drawCircle(xBall2,yBall2,radiusBall2,BLACK,FILL);       // Erase previous ball position
   xBall2+=(dirx2*speedBall2);                                 // Calculate new x coordinate for ball2
   yBall2+=(diry2*speedBall2);                                 // Calculate new y coordinate for ball2  
   lcd.drawCircle(xBall2,yBall2,radiusBall2,colourBall2,FILL); // Draw new ball position
   if((xBall2+speedBall2+radiusBall2)>318 | (xBall2-speedBall2-radiusBall2)<=1){  // if ball reaches the left or right corner, we invert moving direction
    dirx2= dirx2*(-1);                                         // Invert the moving direction by multiplying by -1
   }
   if((yBall2+speedBall2+radiusBall2)>238 | (yBall2-speedBall2-radiusBall2)<=1){  // if ball reaches the top or bottom corner, we invert moving direction 
     diry2= diry2*(-1);                                        // Invert the moving direction by multiplying by -1
   }                        
}

/***************************************************/
//Function that updates the current position of the ball3
void moveBall3(){                    
   lcd.drawCircle(xBall3,yBall3,radiusBall3,BLACK,FILL);       // Erase previous ball position
   xBall3+=(dirx3*speedBall3);                                 // Calculate new x coordinate for ball3
   yBall3+=(diry3*speedBall3);                                 // Calculate new y coordinate for ball3  
   lcd.drawCircle(xBall3,yBall3,radiusBall3,colourBall3,FILL); // Draw new ball position
   if((xBall3+speedBall3+radiusBall3)>318 | (xBall3-speedBall3-radiusBall3)<=1){  // if ball reaches the left or right corner, we invert moving direction
    dirx3= dirx3*(-1);                                         // Invert the moving direction by multiplying by -1
   }
   if((yBall3+speedBall3+radiusBall3)>238 | (yBall3-speedBall3-radiusBall3)<=1){  // if ball reaches the top or bottom corner, we invert moving direction 
     diry3= diry3*(-1);                                        // Invert the moving direction by multiplying by -1
   }                        
}

/***************************************************/
//Function that updates the current position of the ball4
void moveBall4(){
   lcd.drawCircle(xBall4,yBall4,radiusBall4,BLACK,UNFILL);       // Erase previous ball position
   xBall4+=(dirx4*speedBall4);                                   // Calculate new x coordinate for ball4 
   yBall4+=(diry4*speedBall4);                                   // Calculate new y coordinate for ball4  
   lcd.drawCircle(xBall4,yBall4,radiusBall4,colourBall4,UNFILL); // Draw new ball position
   if((xBall4+speedBall4+radiusBall4)>318 | (xBall4-speedBall4-radiusBall4)<=1){           // if ball reaches the left or right corner, we invert moving direction 
    dirx4= dirx4*(-1);                                         // Invert the moving direction by multiplying by -1
   }
   if((yBall4+speedBall4+radiusBall4)>238 | (yBall4-speedBall4-radiusBall4)<=1){           // if ball reaches the top or bottom corner, we invert moving direction 
    diry4= diry4*(-1);                                         // Invert the moving direction by multiplying by -1
   }                       
}

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop 
  lcd.baudChange(1000000); //set a fast baud! for fast drawing
  lcd.drawRectangle(0,0,319,239,MAGENTA,UNFILL); //draw corners
  
  while(1){             // Loop forever
    moveBall1();        // move ball1
    moveBall2();        // move ball2
    moveBall3();        // move ball3
    moveBall4();        // move ball4
    delay(15);          // wait a little
  }
}
