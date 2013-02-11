/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2012.
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

//Each time we use the touchscreen we must define a int array that stores the X and Y readed or touched coordinates.
int touch[2];
//Each time we use the touchicon we must define a char array that stores the name of the touched icon.
char icon[3];

char pixelArray[3];                     //Array to store the RGB888 pixel obtained with memoryRead()


//Main applications, the next applications are called by the main loop menu
/**************************************************/
/**************************************************/
/**************************************************/
/**************************************************/
//clock application
char clock(){
  int hours=4,mins=48,secs=0;
  int halfx=160 ,halfy=129;
  int xs,ys,xm,ym,xh,yh,n;
  int angleH,angleM,angleS;
  int handHour=45;//hand size
  int handMin=57;//hand size
  int handSec=62;//hand size 
  int colBackClk,colHour,colMin,colSec; 
  char carClk=1,clockNextFlag;
  
  while(1){                       //we loop between clocks until a touch on icons
    switch(carClk){
      case 1:                      
        lcd.imageSD(0,0,"oldclk"); //load the clock face
        colHour=BLACK;             //change the colour of the clock hands
        colMin=BLACK;
        colSec=RED;
        handHour=45;               //hands size
        handMin=57;                 
        handSec=62;
      break;
      case 2:
        lcd.imageSD(0,0,"colclk"); //load the clock face
        colHour=RED;               //change the colour of the clock hands
        colMin=BLUE;
        colSec=YELLOW;    
        handHour=58;               //hands size
        handMin=65;
        handSec=70;
      break;
      case 3:
        lcd.imageSD(0,0,"purclk"); //load the clock face
        colHour=WHITE;             //change the colour of the clock hands
        colMin=WHITE;
        colSec=WHITE;
        handHour=47;               //hands size
        handMin=55;        
        handSec=64;
      break;
      default:
      break;        
    }
    lcd.drawRectangle(0,0,319,14,0x9CB2,1);             //draw upper bar
    lcd.imageSD(10,2,"battery");                        //draw image of battery
    lcd.memoryRead(halfx,halfy,halfx,halfy,pixelArray); //This function return a 24 bit pixel array, 
    colBackClk=RGB888ToRGB565(pixelArray);              //we get the back colour of the clock to erase the hands with the same colour   
    clockNextFlag=0;                                    //turn off next clock flag          
    while(clockNextFlag==0){
      //Do some Math to get the second point of the clock hands. (first point is always the center of the clock)
      angleS=secs*6;                           //get the current seconds in angle form, a circle have 360 degrees divided by 60 seconds = 6, then we multiply the 6 by the current seconds to get current angle
      xs=(sin((angleS*3.14)/180)) * handSec;   //get X component of the second's hand
      ys=(cos((angleS*3.14)/180)) * handSec;   //get Y component of the second's hand
      angleM=mins*6;                           //get the current minutes in angle form, a circle have 360 degrees divided by 60 minutes = 6, then we multiply the 6 by the current minutes to get current angle
      xm=(sin((angleM*3.14)/180)) * handMin;   //get X component of the minutes's hand
      ym=(cos((angleM*3.14)/180)) * handMin;   //get Y component of the minutes's hand 
      angleH=hours*30;                         //get the current hours in angle form, a circle have 360 degrees divided by 12 hours = 30, then we multiply the 30 by the current hours to get current angle
      xh=(sin((angleH*3.14)/180)) * handHour;  //get X component of the hours's hand
      yh=(cos((angleH*3.14)/180)) * handHour;  //get Y component of the hours's hand
     
      //Draw current time hands  
      lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,colMin);  // Draw the minutes hand, first point is the center of the clock, and the second is the point obtained by doing math
      lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,colHour); // Draw the hours hand, first point is the center of the clock, and the second is the point obtained by doing math
      lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,colSec);  // Draw the seconds hand, first point is the center of the clock, and the second is the point obtained by doing math
      lcd.drawCircle(halfx,halfy,3,colSec,FILL);           // Draw the center of the second's hand
     
      for(n=0;n<210;n++){                                  // loop for about one second delay (we dont need to explain why we're waiting one second, right?)
        if(lcd.touchScreen(touch)){
          carClk++;                                        // increase clock Counter to select and load next clock
          if(carClk==4){
            carClk=1;
          }                   
          clockNextFlag=1;                                 // turn on flag to change clock
          break;
        }
        if(lcd.touchIcon(icon)){                           // if we receive a touch on icons we exit
          return 0;                                        // exit
        }              
      }
      
      //time managing
      secs++;                                         // increase seconds
      if(secs==60){                                   // if we reach 60 seconds
        mins++;                                       // increase the minutes
        if(mins==60){                                 // if we reach 60 minutes
          hours++;                                    // increase the minutes
          if(hours==12){                              // if we reach 12 hours
            hours=0;                                  // clear hours
          } 
          mins=0;                                     // clear minutes
        }            
        secs=0;                                       // clear seconds
      }                      
 
      //Erase all hands         
      lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,colBackClk); // Erase Second's hand
      lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,colBackClk); // Erase Minute's hand
      lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,colBackClk); // Erase Hour's hand            
    }
  }    
}

/**************************************************/
/**************************************************/
//calc application
void calculator(){
  unsigned char auxCalc=0;
  char number=0,sums=0;
  char num1[2]={0}; 
  char num2[2]={0}; 
  char result[4]={0};
  char operation[2]={0};
  
  lcd.imageSD(0,0,"Calc");                           //load calc design
  lcd.drawRectangle(0,0,319,14,0x9CB2,1);            //draw upper bar
  lcd.imageSD(10,2,"battery");                       //draw battery icon
  lcd.string(224,34,255,65,BLACK,FONT7,TRANS,"0");   //draw numbers
  lcd.string(80,36,100,55,BLACK,FONT0,TRANS,"0");  
  
  //Start application
  while(1){                               //while touch on icons
    while(lcd.touchScreen(touch)==0 & lcd.touchIcon(icon)==0); //wait for a touch to do something
    if(lcd.touchIcon(icon)==1){           //if the received touch was on any icon we go to main menu 
      break;  
    }         
    if(touch[YCOORD]>73 & touch[YCOORD]<101){        //first row       
      if(touch[XCOORD]>74 & touch[XCOORD]<117){
        auxCalc='E'; 
      }else if(touch[XCOORD]>116 & touch[XCOORD]<161){
        auxCalc='I';
      }else if(touch[XCOORD]>161 & touch[XCOORD]<205){
        auxCalc='/';
      }else if(touch[XCOORD]>204 & touch[XCOORD]<249){
        auxCalc='X';
      }
    }else if(touch[YCOORD]>100 & touch[YCOORD]<130){ //second row
      if(touch[XCOORD]>74 & touch[XCOORD]<117){
        auxCalc=7; 
      }else if(touch[XCOORD]>116 & touch[XCOORD]<161){
        auxCalc=8;
      }else if(touch[XCOORD]>161 & touch[XCOORD]<205){
        auxCalc=9;
      }else if(touch[XCOORD]>204 & touch[XCOORD]<249){
        auxCalc='-';
      }                
    }else if(touch[YCOORD]>129 & touch[YCOORD]<159){ //third row
      if(touch[XCOORD]>74 & touch[XCOORD]<117){
        auxCalc=4; 
      }else if(touch[XCOORD]>116 & touch[XCOORD]<161){
        auxCalc=5;
      }else if(touch[XCOORD]>161 & touch[XCOORD]<205){
        auxCalc=6;
      }else if(touch[XCOORD]>204 & touch[XCOORD]<249){
        auxCalc='+';
      }                     
    }else if(touch[YCOORD]>158 & touch[YCOORD]<188){ //fourth row
      if(touch[XCOORD]>74 & touch[XCOORD]<117){
        auxCalc=1; 
      }else if(touch[XCOORD]>116 & touch[XCOORD]<161){
        auxCalc=2;
      }else if(touch[XCOORD]>161 & touch[XCOORD]<205){
        auxCalc=3;
      }else if(touch[XCOORD]>204 & touch[XCOORD]<249){
        auxCalc='R';
      }         
    }else if(touch[YCOORD]>187 & touch[YCOORD]<215){ //fifth row
      if(touch[XCOORD]>74 & touch[XCOORD]<117){
        auxCalc=0; 
      }else if(touch[XCOORD]>116 & touch[XCOORD]<161){
        auxCalc=0;
      }else if(touch[XCOORD]>204 & touch[XCOORD]<249){
        auxCalc='R';
      } 
    }else{
      auxCalc='N';
    }
    if(number==0){               //get first number
      if(auxCalc<10){
        num1[0]=auxCalc+0x30;               
      }else{
        if(auxCalc=='E'){                  
          num1[0]=0x30;                
        }else{                  
          operation[0]=auxCalc;
          if(operation[0]!='R' & operation[0]!='N' & operation[0]!='I'){
            number++; 
            lcd.drawRectangle(224,34,248,58,0xD6B6,FILL);
            delay(200);
            lcd.string(90,36,100,55,BLACK,FONT0,TRANS,operation);                  
          }                                                     
        }                            
      }
      lcd.drawRectangle(80,36,87,46,0xD6B6,FILL);              
      lcd.drawRectangle(224,34,248,58,0xD6B6,FILL);
      lcd.string(224,34,255,65,BLACK,FONT7,TRANS,num1);
      lcd.string(80,36,100,55,BLACK,FONT0,TRANS,num1);
      num2[0]=0; 
    }else if (number==1){       //get second number
      if(auxCalc<10){
        num2[0]=auxCalc+0x30;              
      }else{
        if(auxCalc=='E'){
            num2[0]=0x30; 
        }else{                                                         
          if(auxCalc=='R'){
            switch(operation[0]){
              case '+':
                sums=(num1[0]-0x30);
                sums+=(num2[0]-0x30);                          
              break;
              case '-':
                sums=(num1[0]-0x30);
                sums-=(num2[0]-0x30);                          
              break;
              case 'X':
                sums=(num1[0]-0x30);
                sums*=(num2[0]-0x30);                          
              break;
              case '/':
                sums=(num1[0]-0x30);
                sums/=(num2[0]-0x30);                                                  
              break;  
              default:
                sums=(num1[0]-0x30);
                sums+=(num2[0]-0x30); 
              break;                                                               
            }       
            if(sums<0){
              result[0]='-'; 
              result[1]=(-1*(sums/10))+0x30;
              result[2]=(-1*(sums%10))+0x30;
            }else{
              result[0]=' ';                                   
              result[1]=(sums/10)+0x30;
              result[2]=(sums%10)+0x30;
            }                        
            lcd.string(100,36,110,55,BLACK,FONT0,TRANS,num2);
            lcd.string(110,36,120,55,BLACK,FONT0,TRANS,"=\0");
            lcd.drawRectangle(224,34,248,58,0xD6B6,FILL);
            lcd.string(192,34,255,65,BLACK,FONT7,TRANS,result);                                              
            number++;    
            delay(200);                                                                  
          }                                                                        
        }                             
      } 
      if(number<2){
        lcd.drawRectangle(100,36,107,46,0xD6B6,FILL);              
        lcd.drawRectangle(224,34,248,58,0xD6B6,FILL);
        lcd.string(224,34,255,65,BLACK,FONT7,TRANS,num2);
        lcd.string(100,36,110,55,BLACK,FONT0,TRANS,num2);
      }
    }else{
      lcd.drawRectangle(75,34,248,58,0xD6B6,FILL);
      number=0;
    }            
  }     
}

/**************************************************/
/**************************************************/
//notes application
void notes(){
  lcd.imageSD(0,0,"notes");                   //load notes design
  lcd.drawRectangle(0,0,319,14,0x9CB2,FILL);  //draw upper bar
  lcd.imageSD(10,2,"battery");                //draw battery
  while(1){          
    while(lcd.touchScreen(touch)==0 & lcd.touchIcon(icon)==0); //wait for a touch to do something
    if(lcd.touchIcon(icon)==1){               //if the received touch was on any icon we exit go to main menu 
      break;  
    }   
    if(touch[YCOORD]>66){ 
      lcd.drawCircle(touch[XCOORD],touch[YCOORD],2,BLACK,FILL);
    }else{
      if(touch[XCOORD]<61){
        break;
      }else if(touch[XCOORD]>280){            //reload all
        lcd.imageSD(0,0,"notes");
        lcd.drawRectangle(0,0,319,14,0x9CB2,FILL);
        lcd.imageSD(10,2,"battery");             
      }
    }                                 
 }                                 
}

/**************************************************/
/**************************************************/
//pong application
void pong(){
  
  char radiusBall2=8;
  char radiusBall1=10;  
  int speedBall1=2; //ball1 moving speed - amount of pixels that ball move each time
  int speedBall2=3; //ball2 moving speed - amount of pixels that ball move each time 
  int dirx1=-1;     //xball1 initial negative direction
  int diry1=1;      //yball1 initial positive direction
  int xBall1=200;   //x initial position of ball1
  int yBall1;       //y position of ball1
  int dirx2=1;      //xball2 initial positive direction
  int diry2=-1;     //yball2 initial negative direction
  int xBall2=50;    //x initial position of ball2
  int yBall2;       //y position of ball2
  
  //variables used by Pong data
  char score[7]={0,0,' ','P','T','S',0x00}; //array to save score
  char points=0;            
  char gameOver=0;        //game over flag
  int speedCounter=0;     //Counter that saves the speed 
  char ball1Active=1;     //acrive ball flag
  char ball2Active=1;     //active ball flag 
  int barSize = 60;       //size of bar in pixels 
  int bar=50;             //initial x position of the bar   
  int barCenter = (barSize/2)+bar; //we need to know the center of the bar
  int pongBack=0x6350;    //pong background colour
   
  //define bouncing corners 
  int bottomx1= (25+radiusBall1);
  int topx1   = (319-25-radiusBall1-1);
  int bottomy1= (25+radiusBall1);
  int topy1   = (239-30-radiusBall1-1);
  int bottomx2= (25+radiusBall2);
  int topx2   = (319-25-radiusBall2-1);
  int bottomy2= (25+radiusBall2);
  int topy2   = (239-30-radiusBall2-1);    
  
  unsigned char i;
  char buffer[3];
   
  yBall1=random(25+radiusBall1,120); //y initial position of ball1 
  yBall2=random(25+radiusBall2,120); //y initial position of ball2
    
  lcd.imageSD(0,0,"pong");                                               //load pong design
  lcd.drawRectangle(0,0,319,14,0x9CB2,FILL);                             //draw bar
  lcd.imageSD(10,2,"battery");                                           //draw battery
  lcd.string(110,100,250,120,GREEN,FONT0,COLOUR,"Touch to Begin");       //draw instructions
  while(lcd.touchScreen(touch)==0);                                      //wait a touch to begin
  lcd.drawRectangle(25,25,294,214,pongBack,FILL);                        //draw arena
  lcd.drawRectangle(24,24,295,215,GREEN,UNFILL);                         //corners
  lcd.drawLine(bar,209,bar+barSize,209,WHITE);                           //draw Bar   
    
  while(gameOver==0){                                                    //while game over flag is zero                          
    buffer[0]=(points/10)+0x30, buffer[1]=(points%10)+0x30, buffer[2]=0; //fill buffer that counts
    lcd.string(2,16,30,35,RED,FONT3,COLOUR,buffer);                      //display current points
      for(i=0;i<5;i++){                                                  //check 5 times if the player touches the screen
        if(lcd.touchScreen(touch)){                                      //if we receive a touch then we move the bar to touched side
          lcd.drawLine(bar,209,bar+barSize,209,pongBack);                //erase previous Bar    
          if(touch[XCOORD]>barCenter){                                   //if we need to move the bar to the right           
            bar+=8;                                                      //move the bar to the right  8 pixels
            if((bar+barSize)>293){                                       //if the bar reach the right corner
              bar=293-barSize;      
            }              
            barCenter=bar+(barSize/2);                                   //set new center position of the bar
          }else{                                                         //move the bar to the left                                   
            bar-=8;                                                      //move the bar to the left 8 pixels 
            if(bar<25){                                                  //if the bar reach the left corner
              bar=25;  
            }              
            barCenter=bar+(barSize/2);                                   //set new center position of the bar
          }
          lcd.drawLine(bar,209,bar+barSize,209,WHITE);                   //draw the new bar at the new position
        }
      }
      //we update the balls
      if(ball1Active){                                                   //if we haven't lost the ball1         
        /***************************************************/
        //This its similar as moveBall1() function of pong example
        //update the actual position of the ball1        
        lcd.drawCircle(xBall1,yBall1,radiusBall1,pongBack,UNFILL);     // Erase previous ball position
        xBall1+=(dirx1*speedBall1);                                    // Calculate new x coordinate for ball1 
        yBall1+=(diry1*speedBall1);                                    // Calculate new y coordinate for ball1  
        lcd.drawCircle(xBall1,yBall1,radiusBall1,GREEN,UNFILL);        // Draw new ball position
        if((xBall1+speedBall1)>topx1 | (xBall1-speedBall1)<=bottomx1){ // if ball reaches the left or right corner, we invert moving direction 
         dirx1= dirx1*(-1);
        }
        if((yBall1+speedBall1)>topy1 | (yBall1-speedBall1)<=bottomy1){ // if ball reaches the top or bottom corner, we invert moving direction 
         if((yBall1-speedBall1)<=bottomy1){                            // Bounce on top, only invert moving direction
           diry1= diry1*(-1);                                          // We invert the moving direction by multiplying by -1
         }else{                                                        // Bounce on bottom, check if inside the bar       
           if((xBall1+speedBall1)>bar & (xBall1-speedBall1)<(bar+barSize)){  //if bounce inside the bar
             diry1= diry1*(-1);                                        // We invert the moving direction by multiplying by -1
             points++;                                                 // Increase player current points
             speedCounter++;                                           // Increase the speed counter
             if(speedCounter>9){                                       // If we reach 10 counts we increase the ball1 bouncing speed
               speedBall1++;          
               speedCounter=0;                                          // Reset the counter
             }                           
           }else{                                                      // Bounce outside the bar
             ball1Active=0;                                            // Clear ball1 active flag
             lcd.drawCircle(xBall1,yBall1,radiusBall1,pongBack,UNFILL);// Delete this ball because bounce outside of the bar        
             if(ball1Active==0 & ball2Active==0){                      // if we have lost both balls     
              gameOver=1;                                              // Set game over flag
             }         
          }
        }
       }          
      }
      if(ball2Active){                                                 //if we haven't lost the ball2
        /***************************************************/
        //This its similar as moveBall2() function of pong example
        //update the actual position of the ball2          
        lcd.drawCircle(xBall2,yBall2,radiusBall2,pongBack,FILL);       // Erase previous ball position
        xBall2+=(dirx2*speedBall2);                                    // Calculate new x coordinate for ball2 
        yBall2+=(diry2*speedBall2);                                    // Calculate new y coordinate for ball2
        lcd.drawCircle(xBall2,yBall2,radiusBall2,MAGENTA,FILL);        // Draw new ball position
        if((xBall2+speedBall2)>topx2 | (xBall2-speedBall2)<=bottomx2){ // if ball reaches the left or right corner, we invert moving direction 
         dirx2= dirx2*(-1);
        }
        if((yBall2+speedBall2)>topy2 | (yBall2-speedBall2)<=bottomy2){ // if ball reaches the top or bottom corner, we invert moving direction 
         if((yBall2-speedBall2)<=bottomy2){                            // Bounce on top, only invert moving direction
           diry2= diry2*(-1);        
         }else{                                                        // Bounce on bottom, check if inside the bar       
           if((xBall2+radiusBall2)>bar & (xBall2-radiusBall2)<(bar+barSize)){  //if bounce inside the bar
             diry2= diry2*(-1);                                        // We invert the moving direction by multiplying by -1
             points++;                                                 // Increase player current points
             speedCounter++;                                           // Increase the speed counter
             if(speedCounter>9){                                       // If we reach 10 counts we increase the ball1 bouncing speed
               speedBall2++;          
               speedCounter=0;                                         // Reset the counter
             }                            
           }else{                                                      // Bounce outside the bar
             ball2Active=0;                                            // Clear ball1 active flag
             lcd.drawCircle(xBall2,yBall2,radiusBall2,pongBack,FILL);  // Delete this ball because bounce outside of the bar        
             if(ball1Active==0 & ball2Active==0){                      // if we have lost both balls     
               gameOver=1;                                             // Set game over flag
             }         
           }
         }
       } 
     }
  }
  //game over - proceed to show final score
  lcd.string(80,80,272,140,RED,FONT5,TRANS,"Game Over");
  score[0]=(points/10)+0x30;                                            //convert points to ascii format and store them on the score buffer
  score[1]=(points%10)+0x30;                                            //convert points to ascii format and store them on the score buffer
  lcd.string(105,110,272,140,YELLOW,FONT5,TRANS,score);
  lcd.string(100,135,250,180,GREEN,FONT3,TRANS,"Touch to Exit");          
  delay(1000);
  while(lcd.touchScreen(touch)==0);                                     //wait for a touch to exit
}

/**************************************************/
/**************************************************/
//slide show application
void slideShow(){
  char imagesOnSDCard[8][9]={"Peng320","Koala320","Hydra320","Lig320","Sea320","Tul320","Des320","Flow320"}; //array containing the names of the different called images
  char pic=0;
  
  while(1){   //Loop forever in the slide show!
    lcd.imageSD(0,0,imagesOnSDCard[pic]);      //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.imageSD(3,219,"prev");                 //Load the prev icon        
    lcd.imageSD(300,219,"next");               //Load the next icon
    lcd.drawRectangle(0,0,319,14,0x9CB2,FILL); //draw upper bar
    lcd.imageSD(10,2,"battery");               //draw battery    
       
    while(lcd.touchScreen(touch)==0 & lcd.touchIcon(icon)==0); //wait for a touch to do something
    if(lcd.touchIcon(icon)==1){                //if the received touch was on any icon we exit go to main menu 
      break;  
    } 
    
    //check if we go to the next image, or to the previous one
    if(touch[XCOORD]>160){                  //if the received touch was on the right middle of the screen we advance the image, else we decrease and go to previous image
      pic++;                                //decrease image selector
      if(pic>7){                            //if we reach the position of the last image, we restart to image 0
        pic=0;                 
      }        
    }else{
      pic--;    
      if(pic<0){                            //if we reach the position of the first image, we move to image 7
        pic=7;  
      }    
    }   
  }
}  

/**************************************************/
/**************************************************/
//settings application, brightness adjust
void settings(){
  static int bright=127;                                       //Maximum bright is set by default  133 min 14
  static int buttonCen=271;                                    //button center, static variables to avoid losing the parameters even if we go to main menu
  
    lcd.imageSD(0,0,"Bright");                                 //Load image from SD card, image is 320x240(full screen) so we load it from top left corner X:0,Y:0   
    lcd.drawRectangle(0,0,319,14,0x9CB2,FILL);                 //draw upper bar
    lcd.imageSD(10,2,"battery");                               //draw battery  
    
  while(1){   //Loop forever in the settings!    
    lcd.drawRectangle(40,64,(bright*2)+12,66,0x4C7C,FILL);     //draw brightness bar  266 max  40 min 
    lcd.drawRectangle((bright*2)+12,64,266,66,WHITE,FILL);     //fill the rest of the bar with white     
    lcd.imageSD((bright*2)+12,57,"button");                    //Load the button icon   266 max pos X, 40 min X pos   
    delay(100);                                                //delay to avoid fast change and flickering
    
    while(lcd.touchScreen(touch)==0 & lcd.touchIcon(icon)==0); //wait for a touch to do something
    if(lcd.touchIcon(icon)==1){                                //if the received touch was on any icon we exit go to main menu 
      break;  
    }
    
    //touch on Screen, change brightness and draw button icon
    if(touch[YCOORD]>55 & touch[YCOORD]<85 ){                  //if the previous touch was on active area
      lcd.imageSD((bright*2)+12,57,"clrBar");                  //clear the button icon       
           
      //check where to move left or right
      if(touch[XCOORD]>buttonCen){                             //if we need to move the bar to the right        
        bright+=10;                                            //increase the brightness
        buttonCen+=22;                                         //increase the center of the button
        if(bright>127){                                        //if the button reach the right corner
          bright=127;                                          //set maximum bright
          buttonCen=271;                                       //set maximum button center          
        }              
      }else{                                                   //move the bar to the left                                          
        bright-=10;                                            //decrease the brightness
        buttonCen-=22;                                         //decrease the center of the button
        if(bright<14){                                         //if the button reach the left corner
          bright=14;                                           //set minimum bright
          buttonCen=40;                                        //set minimum button center          
        }           
      }
      lcd.bright(bright);                                      //set new brightness value to SMART GPU          
    }
  } 
}

/**************************************************/
/**************************************************/
//google maps application
void googleMaps(){
  char mapsOnSDCard[10][9]={"map0","map1","map2","map3","map4","map5","map6","map7","map8","map9"}; //array containing the names of the different called maps  
  char maps=0,nothing=1;

  while(1){   //Loop forever in the slide show!
    if(nothing!=0){                              //do something
      lcd.imageSD(0,0,mapsOnSDCard[maps]);       //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
      lcd.drawRectangle(0,0,319,14,0x9CB2,FILL); //draw upper bar
      lcd.imageSD(10,2,"battery");               //draw battery
      lcd.imageSD(5,25,"barmap");                //draw zoom bar
    }
    while(lcd.touchScreen(touch)==0 & lcd.touchIcon(icon)==0); //wait for a touch to do something
    if(lcd.touchIcon(icon)==1){                //if the received touch was on any icon we exit go to main menu 
      break;  
    } 
    
    if(touch[XCOORD]<25){                     //touch on bar
      if(touch[YCOORD]<120){                  //touch on upper side of zoom bar
        maps++;
        if(maps>10){
          maps=10;
        }
      }else{                                  //touch on lower side of zoom bar
        maps--;
        if(maps<1){
          maps=1;  
        }          
      }
       nothing=1;                             //prepare to do new image loading
    }else{                                    //touch on inactive area
       nothing=0;                             //do nothing and get another touch  
    }
  }
}  
 
/**************************************************/
/**************************************************/
//paint application   
void paint(){
  unsigned char penSize=1;
  int colPaint=BLACK;
  char pen[4]={'x','0','1',0x00};                     //Array that show the current penSize
       
  //Load paint design
  lcd.imageSD(0,0,"paint");                           //load paint image
  lcd.string(7,54,48,65,GREEN,FONT1,FILL,"Erase");    //draw Erase word
  lcd.string(77,54,110,65,GREEN,FONT1,FILL,pen);      //draw penSize 
  lcd.drawRectangle(0,0,319,14,0x9CB2,FILL);          //draw upper bar
  lcd.imageSD(10,2,"battery");                        //draw battery  
  
   while(1){   //Start the Paint application
     while(lcd.touchScreen(touch)==0 & lcd.touchIcon(icon)==0); //wait for a touch to do something
     if(lcd.touchIcon(icon)==1){                //if the received touch was on any icon we exit go to main menu 
       break;  
     }     
   
     if(touch[YCOORD]<67){                             //the touch was on the menu
       if(touch[XCOORD]<45){                           //touch on erase circle
         lcd.drawRectangle(0,67,319,239,WHITE,1);      //Draw a white rectangle on drawing area
       }else if(touch[XCOORD]<75){                     //touch to select the eraser
         colPaint=WHITE;
         lcd.drawCircle(25,34,14,colPaint,FILL);       //draw WHITE colour circle on top left corner           
       }else if(touch[XCOORD]<108){                    //touch to change pen Size 
         penSize=penSize*2;                            //double the penSize
         if(penSize==16){                              //maximum pen size = 8, if we reach 16 we set to 1.
           penSize=1;
         }          
         pen[1]=(penSize/10)+0x30;                     //get the tens of penSize and convert them to ascii
         pen[2]=(penSize%10)+0x30;                     //get the ones of penSize and convert them to ascii
         lcd.string(77,54,110,65,GREEN,FONT1,FILL,pen);//draw penSize 
         delay(500);                                   //delay to avoid fast penSize changing            
       }else if(touch[XCOORD]<312 & touch[YCOORD]>20 & touch[YCOORD]<59){                     //touch on the colours bar                  
         lcd.memoryRead(touch[XCOORD],touch[YCOORD],touch[XCOORD],touch[YCOORD],pixelArray);  //assign new colour based on touch coordinates and memory read, this function return a 24 bit pixel array, 
         colPaint=RGB888ToRGB565(pixelArray);
         lcd.drawCircle(25,34,14,colPaint,FILL);                                              //draw new selected colour on top left corner           
       }                
    }else{                                            //Touch on drawing area
       if((touch[YCOORD]-penSize)<67){                 // If the touch was very close to the menu, we compensate the radius
         touch[YCOORD]=touch[YCOORD]+penSize;
       }
       lcd.drawCircle(touch[XCOORD],touch[YCOORD],penSize,colPaint,FILL);                    //Draw
    }
  }   
}

//End of applications, the next function is for pixel format conversion
/**************************************************/
/**************************************************/
//Funcion to convert a 3 byte array to an int RGB565
int RGB888ToRGB565(char pixBuffer[]){   //get an array of 3 bytes( red, green, blue), and convert them to RGB565 returned in an int
  unsigned char R,G,B;
  unsigned int col;
  unsigned long colour;
  
  R=pixBuffer[0];
  G=pixBuffer[1];
  B=pixBuffer[2]; 
  ((unsigned char *) &colour)[1]=(R & 0xF8);
  R=G;
  G=G>>5;
  ((unsigned char *) &colour)[1]|=G;
  G=(R<<3)& 0xE0;
  ((unsigned char *) &colour)[0]=B;
  ((unsigned char *) &colour)[0]=((unsigned char *) &colour)[0]>>3;  
  ((unsigned char *) &colour)[0]|=G;
  col=colour;
  return col;
}


/**************************************************/
/**************************************************/
//Initial setup
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

/**************************************************/
/****************** MAIN LOOP *********************/
/**************************************************/
/**************************************************/
void loop() { //main loop
  unsigned char ic;
  
  lcd.baudChange(2000000);         //set high baud for advanced applications
  
  while(1){
    //load menu and bar
    lcd.imageSD(0,0,"IpMenu");   
    lcd.drawRectangle(0,0,319,14,0x9CB2,1);
    lcd.imageSD(10,2,"battery"); 
    
    //wait for a touch on screen to do something
    while(lcd.touchScreen(touch)==0);   
    
    //obtain icon number
    if(touch[XCOORD]<84){       //if X coordinate is less than 84
      ic=1;      
    }else if(touch[XCOORD]<160){//if X coordinate is less than 160
      ic=2;
    }else if(touch[XCOORD]<235){//if X coordinate is less than 235
      ic=3;      
    }else{                      //then X coordinate is between 235-319
      ic=4;
    }  
    if(touch[YCOORD]>128){      //if Y is greater than 134, touch was on the bottom half of the screen
      ic=ic+4;
    }
    
    //begin application based on icon number  
    switch(ic){                 //now that we know a touch was made on a specified icon:
      case 1:                   //case 1 (clock)
        clock();
      break;                    //end of case 1
      
      case 2:                   //case 2 (calculator)
        calculator();  
      break;                    //end of case 2 

      case 3:                   //case 3 (notes) 
        notes();
      break;                    //end of case 3 

      case 4:                   //case 4 (pong) 
        pong();
      break;                    //end of case 4 

      case 5:                   //case 5 (slide show) 
        slideShow();
      break;                    //end case 5 

      case 6:                   //case 6 (settings)
        settings();
      break;                    //end case 6

      case 7:                   //case 7 (googleMaps)
        googleMaps();                 
      break;                    //end of case 7 

      case 8:                   //case 8 (paintPro)
        paint();             
      break;                    //end of case 8
      
      default:                  //default for any other case
      break;                    //do nothing
    } 
  }  
}
