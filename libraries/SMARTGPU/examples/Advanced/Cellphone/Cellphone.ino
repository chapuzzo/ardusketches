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

//Global variables
int hours=11,mins=19,secs=33;
char contactName[7][20]={"Adam Playford","Akash Krishnani","Alexis Barta","Alice Alcantara","Amanda Bannout","Andrea Jahanbozorg","Anna Kaltenbrunner"};

//Main applications, the next applications are called by the main loop menu
/**************************************************/
/**************************************************/
/**************************************************/
/**************************************************/
//clock application THIS METHOD IS 100% RECOMMENDED TO BE EXECUTED WITH TIMER INTERRUPTS, BUT DUE TO SKETCH SIMPLICITY WE CREATED THIS WITH DELAYS INSTEAD OF TIMERS
char clock(unsigned char drawHands){
  int xs,ys,xm,ym,xh,yh,n;
  int angleH,angleM,angleS;
  int halfx=208 ,halfy=50, radiusClk=25; //Clock related sizes  
  int handHour=16;                       //hand size
  int handMin=20;                        //hand size
  int handSec=23;                        //hand size 
  char time[9]={0x30,0x30,':',0x30,0x30,':',0x30,0x30,0x00};
  
  while(1){                              //we loop between clocks until a touch on something
    if(drawHands==1){   
      lcd.drawCircle(halfx,halfy,radiusClk,WHITE,FILL);
      lcd.drawCircle(halfx,halfy,radiusClk,BLUE,UNFILL);    
    }    
    while(1){
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
     
      //Draw current time hands if drawHands=1
      if(drawHands==1){ 
        lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,BLACK);  // Draw the minutes hand, first point is the center of the clock, and the second is the point obtained by doing math
        lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,BLACK);  // Draw the hours hand, first point is the center of the clock, and the second is the point obtained by doing math
        lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,RED);    // Draw the seconds hand, first point is the center of the clock, and the second is the point obtained by doing math      
      }      
      //Draw text time on top of screen 
      time[0]=(hours/10)+0x30;                              // convert hours to ascii format
      time[1]=(hours%10)+0x30;                              // convert hours to ascii format
      time[3]=(mins/10)+0x30;                               // convert mins to ascii format 
      time[4]=(mins%10)+0x30;                               // convert mins to ascii format 
      time[6]=(secs/10)+0x30;                               // convert secs to ascii format 
      time[7]=(secs%10)+0x30;                               // convert secs to ascii format       
      lcd.string(170,3,239,30,WHITE,FONT3,FILL,time);     
     
      for(n=0;n<420;n++){                                   // loop for about one second delay (we dont need to explain why we're waiting one second, right?)
        if(lcd.touchScreen(touch)){                         //if we receive a touch on screen
          return 0;                                         //Break and go to process touch
        }         
      }      
      //time managing
      secs++;                                               // increase seconds
      if(secs==60){                                         // if we reach 60 seconds
        mins++;                                             // increase the minutes
        if(mins==60){                                       // if we reach 60 minutes
          hours++;                                          // increase the minutes
          if(hours==12){                                    // if we reach 12 hours
            hours=0;                                        // clear hours
          } 
          mins=0;                                           // clear minutes
        }            
        secs=0;                                             // clear seconds
      }                       
      //Erase all hands    
      if(drawHands==1){       
        lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,WHITE); // Erase Second's hand
        lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,WHITE); // Erase Minute's hand
        lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,WHITE); // Erase Hour's hand            
      }
    }
  }    
}

/**************************************************/
/**************************************************/
//notes application
void notes(){

  lcd.imageSD(0,0,"noteP");                  //load notes design
  while(1){          
    clock(0);                                //run clock
    if(touch[YCOORD]<65){                    //Touch on upper Icons
      if(touch[XCOORD]<65){
        break;
      }else if(touch[XCOORD]>190){
        lcd.imageSD(0,0,"noteP");            //load notes design       
      }          
    }else if(touch[YCOORD]<270){             //touch on notepad
      lcd.drawCircle(touch[XCOORD],touch[YCOORD],2,BLACK,FILL);          
    }else{                                   //touch on Main Icons
      if(touch[XCOORD]<60){
        keypad();
      }else if(touch[XCOORD]<120){
        logs(); 
      }else if(touch[XCOORD]<180){
        apps();
      }else{
        contacts();
      }  
      break;
    }                                
  }                                 
}

/**************************************************/
/**************************************************/
//maps application
void maps(){
  char mapsOnSDCard[10][9]={"map0","map1","map2","map3","map4","map5","map6","map7","map8","map9"}; //array containing the names of the different called maps  
  static char maps=0;

  lcd.orientation(LANDSCAPEL);                 //change to landscape L mode 
  while(1){                                    //Loop forever in the slide show!
    lcd.imageSD(0,0,mapsOnSDCard[maps]);       //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.string(90,215,319,239,RED,FONT3,TRANS,"Tap center to Exit"); //Show text
    lcd.imageSD(5,25,"barmap");                //draw zoom bar    
    lcd.imageSD(300,25,"barmap");              //draw zoom bar     
    while(lcd.touchScreen(touch)==0);          //wait for a touch to do something
    //check if we go to the next image, or to the previous one
    if(touch[XCOORD]>100 & touch[XCOORD]<219){  //touch on center, EXIT
      break;    
    }else{                                     //touch on bars
      if(touch[YCOORD]<120){                   //touch on upper side of zoom bar
        maps++;
        if(maps>10){
          maps=10;
        }
      }else{                                   //touch on lower side of zoom bar
        maps--;
        if(maps<1){
          maps=1;  
        }          
      }       
    }
  }  
  lcd.orientation(PORTRAITL);                  //change to portrait mode    
} 

/**************************************************/
/**************************************************/
//settings application, brightness adjust
void settings(){
  static int bright=169;                                       //Maximum bright is set by default
  static int buttonCen=197;                                    //button center, static variables to avoid losing the parameters even if we go to main menu
  
  lcd.imageSD(0,0,"Settings");                                 //Load image from SD card, image is 320x240(full screen) so we load it from top left corner X:0,Y:0   
  //Start application
  while(1){                                 
    lcd.drawRectangle((bright)+33,103,201,105,WHITE,FILL);     //draw the white bar   
    lcd.drawRectangle(33,103,(bright)+33,105,0x4C7C,FILL);     //draw brightness bar
    lcd.imageSD(buttonCen,96,"button");                        //Load the button icon    
    clock(0);                                                  //run clock   
    if(touch[YCOORD]<270){                                     //Touch on bar
      lcd.imageSD(buttonCen,96,"clrBar");                      //clear the button icon  
      //check where to move left or right
      if(touch[XCOORD]>buttonCen){                             //if we need to move the bar to the right        
        bright+=10;                                            //increase the brightness
        buttonCen+=10;                                         //increase the center of the button
        if(bright>169){                                        //if the button reach the right corner
          bright=169;                                          //set maximum bright
          buttonCen=197;                                       //set maximum button center          
        }              
      }else{                                                   //move the bar to the left                                          
        bright-=10;                                            //decrease the brightness
        buttonCen-=10;                                         //decrease the center of the button
        if(bright<1){                                          //if the button reach the left corner
          bright=1;                                            //set minimum bright
          buttonCen=28;                                        //set minimum button center          
        }           
      }
      lcd.bright(bright+20);                                   //set new brightness value to SMART GPU        
    }else{                                                     //touch on Main Icons
      if(touch[XCOORD]<60){
        keypad();
      }else if(touch[XCOORD]<120){
        logs();
      }else if(touch[XCOORD]<180){
        apps();
      }else{
        contacts();
      }
      break;      
    }
  } 
}

/**************************************************/
/**************************************************/
//calendar application
void calendar(){
  lcd.imageSD(0,0,"Calendar");                //load contacts

  //Start application
  while(1){                                  
    clock(0);                                 //run clock        
    if(touch[YCOORD]>270){                    //touch on main icons
      if(touch[XCOORD]<60){
        keypad();
      }else if(touch[XCOORD]<120){
        logs();
      }else if(touch[XCOORD]<180){
        apps();
      }else{
        contacts();
      }
      break;      
    }    
  }     
}

/**************************************************/
/**************************************************/
//photos application
void photos(){
  char imagesOnSDCard[8][9]={"Sea","Lake","Rainbow","Beach","House","House","Bridge","Trees"}; //array containing the names of the different called images
  static char pic=0;
  
  lcd.orientation(LANDSCAPEL);              //change to landscape L mode  
  while(1){  
    lcd.imageSD(0,0,imagesOnSDCard[pic]);   //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.imageSD(3,219,"prev");              //Load the prev icon        
    lcd.imageSD(300,219,"next");            //Load the next icon
    lcd.string(90,215,319,239,RED,FONT3,TRANS,"Tap center to Exit"); //Show text
    while(lcd.touchScreen(touch)==0);       //wait for a touch to do something    
    //check if we go to the next image, or to the previous one
    if(touch[XCOORD]>219){                  //if the received touch was on the right corner of the screen we advance the image, else we decrease and go to previous image
      pic++;                                //decrease image selector
      if(pic>7){                            //if we reach the position of the last image, we restart to image 0
        pic=0;                 
      }        
    }else if(touch[XCOORD]<100){
      pic--;    
      if(pic<0){                            //if we reach the position of the first image, we move to image 7
        pic=7;  
      }    
    }else{                                  //touch on center, EXIT      
      break;
    }   
  }
  lcd.orientation(PORTRAITL);               //change to portrait mode  
} 

/**************************************************/
/**************************************************/
//keypad application
void keypad(){
  unsigned char auxNum=0,numPosition=5,numRow=70;
  
  lcd.imageSD(0,0,"keypad");              //load keypad
  //Start application
  while(1){                               
    clock(0);                             //run clock        
    if(touch[YCOORD]>140){                //touch on keypad
      if(touch[YCOORD]<187){              //first row       
        if(touch[XCOORD]<60){
          auxNum='1'; 
        }else if(touch[XCOORD]<123){
          auxNum='2';
        }else if(touch[XCOORD]<185){
          auxNum='3';
        }else{
          auxNum=0x00;
        }
      }else if(touch[YCOORD]<231){        //second row
        if(touch[XCOORD]<60){
          auxNum='4'; 
        }else if(touch[XCOORD]<123){
          auxNum='5';
        }else if(touch[XCOORD]<185){
          auxNum='6';
        }else{
          call("Unknown Number");
          break;
        }              
      }else if(touch[YCOORD]<275){        //third row
        if(touch[XCOORD]<60){
          auxNum='7'; 
        }else if(touch[XCOORD]<123){
          auxNum='8';
        }else if(touch[XCOORD]<185){
          auxNum='9';
        }else{
          call("Unknown Number");
          break;
        }                    
      }else{                              //fourth row
        if(touch[XCOORD]<60){
          auxNum='*'; 
        }else if(touch[XCOORD]<123){
          auxNum='0';
        }else if(touch[XCOORD]<185){
          auxNum='#';
        }else{
          auxNum=0x00;
        } 
      }           
      if(auxNum==0){
        lcd.drawRectangle(0,70,239,140,BLACK,FILL);                //erase numbers
        numPosition=5;                                             //reset columns
        numRow=70;                                                 //reset Rows        
      }else{ 
        lcd.putLetter(numPosition,numRow,WHITE,FONT7,FILL,auxNum); //write numbers
        numPosition+=17;
        if(numPosition>209){                                       //if we reach column end
          numRow+=32;                                              //jump to next row
          numPosition=5;                                           //reset numPosition(columns)
          if(numRow>102){                                          //if we reach end of rows
            numRow=70;                                             //reset Rows
            lcd.drawRectangle(0,70,239,140,BLACK,FILL);            //erase numbers
          }
        }      
      }
      delay(200);      
    }else if(touch[YCOORD]<70){                                    //touch on main icons
      if(touch[XCOORD]>180){
        contacts();
      }else if(touch[XCOORD]>120){
        apps();
      }else if(touch[XCOORD]>60){
        logs();
      }
      break;                                                       //Exit to main menu      
    }           
  }     
}

/**************************************************/
/**************************************************/
//Call application
char call(char *contact){
  unsigned char i;
  
  lcd.imageSD(0,0,"Call");                              //load call window  
  lcd.string(48,190,192,225,GREEN,FONT3,TRANS,contact); //show contact
  while(1){
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,170,5,YELLOW,FILL);
      if(lcd.touchScreen(touch)){                       //if we receive a touch on screen
          if(touch[YCOORD]>280) return 0;               //Break and return
      }    
      delay(300);      
    }
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,170,5,BLACK,FILL);
      if(lcd.touchScreen(touch)){                       //if we receive a touch on screen
          if(touch[YCOORD]>280) return 0;               //Break and return
      }    
      delay(300);      
    }         
  }
}

/**************************************************/
/**************************************************/
//Logs application
void logs(){
  lcd.imageSD(0,0,"Logs");                    //load calls

  //Start application
  while(1){                                  
    clock(0);                                 //run clock        
    if(touch[YCOORD]>270){                    //touch on main icons
      if(touch[XCOORD]>180){
        contacts();
      }else if(touch[XCOORD]>120){
        apps();
      }else if(touch[XCOORD]<60){
        keypad();
      }
      break;      
    }    
  }     
}

/**************************************************/
/**************************************************/
//Apps
void apps(){
    
  lcd.imageSD(0,0,"Apps");      //load Apps window 
  //Start application
  clock(0);                     //run clock
  if(touch[YCOORD]<130){        //First Row        
    //obtain icon number
    if(touch[XCOORD]<79){       //if X coordinate is less than 79
      notes();      
    }else if(touch[XCOORD]<169){//if X coordinate is less than 169
      maps();
    }else{                      //if X coordinate is less than 239
      settings();      
    } 
  }else if(touch[YCOORD]<255){  //Second Row
    //obtain icon number
    if(touch[XCOORD]<79){       //if X coordinate is less than 79
      //clock();                //IN WORK
    }else if(touch[XCOORD]<169){//if X coordinate is less than 169
      calendar();             
    }else{                      //if X coordinate is less than 239
      photos();      
    }             
  }else{                        //Third row Main Icons
    if(touch[XCOORD]<60){
      keypad();
    }else if(touch[XCOORD]<120){
      logs();
    }else if(touch[XCOORD]>180){
      contacts();
    }
  }
} 

/**************************************************/
/**************************************************/
//contacts application
void contacts(){
  unsigned char x;
  lcd.imageSD(0,0,"Contacts");                //load contacts

  //Start application
  while(1){                                 
    clock(0);                                 //run clock        
    if(touch[YCOORD]>36 & touch[YCOORD]<270){ //touch on contacts
      x=(touch[YCOORD]-36)/34;                //get corresponding touch number contact
      call(contactName[x]);
      break;    
    }else if(touch[YCOORD]>270){              //touch on main icons
      if(touch[XCOORD]<60){
        keypad();
      }else if(touch[XCOORD]<120){
        logs();
      }else if(touch[XCOORD]<180){
        apps();      
      }
      break;      
    }    
  }     
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
  unsigned char i,n; //icon variable
  
  lcd.baudChange(2000000);        //set high baud for advanced applications
  lcd.orientation(PORTRAITL);   //change to portrait mode  

  //Processing Intro
  lcd.imageSD(0,20,"Intro");      //load main menu image  
  for(n=0;n<3;n++){
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,285,5,YELLOW,FILL);
      delay(200);      
    }
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,285,5,BLACK,FILL);
      delay(200);      
    }         
  }  
  
  //Main Menu
  while(1){                       //Forever loop
    lcd.orientation(PORTRAITL);   //change to portrait mode
    lcd.imageSD(0,0,"Menu");      //load main menu image
    clock(1);                     //Run clock app
          
    if(touch[YCOORD]>270){        //if Y coord is greater than 270       
      //obtain icon number and begin application based on touch icon number 
      if(touch[XCOORD]<60){       //if X coordinate is less than 60
        keypad();    
      }else if(touch[XCOORD]<120){//if X coordinate is less than 120
        logs();               
      }else if(touch[XCOORD]<180){//if X coordinate is less than 180
        apps();  
      }else{                      //then X coordinate is between 180-239
        contacts();        
      }    
    }
  }  
}
