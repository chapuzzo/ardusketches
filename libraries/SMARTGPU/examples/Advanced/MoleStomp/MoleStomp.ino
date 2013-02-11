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

#define MOLEHOLE 3        //position of the array where mole hole image is contained
#define HITMOLE 4         //position of the array where hit mole image is contained
#define MISSMOLE 5        //position of the array where miss mole image is contained

//Each time we use the touchscreen we must define a int array that stores the X and Y readed or touched coordinates.
int touch[2];
//Each time we use the touchicon we must define a char array that stores the name of the touched icon.
char icon[3];

char moleType[6][9]={"MoleHap","MoleSee","MoleBad","MoleHole","MolePun","MoleMiss"}; //array containing the names of the different called images

/****************************************************/
//This function call the desired image in the position of the desired hole
void showMole(char mole, char hole){  
  switch(hole){
    case 1:
      lcd.imageSD(38,70,moleType[mole]); // hole 1
    break;
    case 2:
      lcd.imageSD(138,70,moleType[mole]); // hole 2
    break;  
    case 3:
      lcd.imageSD(240,70,moleType[mole]); // hole 3
    break;    
    case 4:
      lcd.imageSD(38,147,moleType[mole]); // hole 4
    break;  
    case 5:
      lcd.imageSD(138,147,moleType[mole]); // hole 5
    break;
    case 6:
      lcd.imageSD(240,147,moleType[mole]); // hole 6
    break;
    default:
    break;
  } 
}

/****************************************************/
//This function returns 1 if a touch has been made in a specified hole
char touchOnHole(char hole){
  char hit=0; 
  
  switch(hole){
    case 1:
      if(touch[XCOORD]>0 & touch[XCOORD]<111 & touch[YCOORD]>65 & touch[YCOORD]<146){   //check if the last touch was inside this area
        hit=1;    
      } 
    break;
    case 2:
      if(touch[XCOORD]>110 & touch[XCOORD]<211 & touch[YCOORD]>65 & touch[YCOORD]<146){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;  
    case 3:
      if(touch[XCOORD]>210 & touch[XCOORD]<320 & touch[YCOORD]>65 & touch[YCOORD]<146){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;    
    case 4:
      if(touch[XCOORD]>0 & touch[XCOORD]<111 & touch[YCOORD]>145 & touch[YCOORD]<240){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;  
    case 5:
      if(touch[XCOORD]>110 & touch[XCOORD]<211 & touch[YCOORD]>145 & touch[YCOORD]<240){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;
    case 6:
      if(touch[XCOORD]>210 & touch[XCOORD]<320 & touch[YCOORD]>145 & touch[YCOORD]<240){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;
    default:
    break;
  }  
  return hit;  
}

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop
  int x;
  char hitFlag=0;
  char hole, mole;
  char moleCounter=20,points=0;
  char pointsTotal[3]={0};         //array to store the points, two digits plus null character = 3
  
  lcd.baudChange(1000000);         //set high baud
  lcd.setTextBackground(BLUE);     //set the all text background to blue
  
 while(1){                         //loop forever the game
  lcd.string(70,90,300,220,RED,FONT7,TRANS,"GET READY!!!"); //show ready string
  delay(1500);
  lcd.imageSD(0,0,"MoleArea");     //show area 
  lcd.string(35,27,50,50,WHITE,FONT3,COLOUR,"00"); //draw the initial points
  
  //Start the game!
  while(moleCounter>0){            //loop the game while moleCounter reaches zero moles
    randomSeed(random(0,65535));   //set different seeds to obtain a good random number 
    mole=random(0,3);              //get a random mole 0-2
    hole=random(1,7);              //get a random hole 0-6
    showMole(mole,hole);           //show the random mole on the random hole
    for(x=0;x<200;x++){            //wait some time for the player hit the mole(less time=more difficulty, more time=easy play)
      if(lcd.touchScreen(touch)){  //if we receive a touch on screen
        if(touchOnHole(hole)){     //if the touch is on the hole of the current mole
          hitFlag=1;               //turn on the hit mole flag
          break;                   //end the waiting time
        }
      }  
    }
    if(hitFlag==1){               //if the last mole was hit
      showMole(HITMOLE,hole);     //we show the hit mole
      points++;                   //increase hit mole counter or points
      hitFlag=0;                  //clear the hit flag
    }else{                        //if the last mole was missed
      showMole(MISSMOLE,hole);    //show the mole hiding
    }
    pointsTotal[0]=(points/10)+0x30;  //get the tens of the points and convert them to ascii
    pointsTotal[1]=(points%10)+0x30;  //get the ones of the points and convert them to ascii
    lcd.string(35,27,50,50,WHITE,FONT3,COLOUR,pointsTotal); //draw the points    
    delay(350);
    showMole(MOLEHOLE,hole);          //show the bare hole
    moleCounter--;                    //decrease the mole counter
  }                                   //end of the game
  
  //Game over, display results
  lcd.string(90,50,300,220,YELLOW,FONT4,TRANS,"Whacked Moles:"); 
  lcd.string(153,75,300,220,BLUE,FONT4,TRANS,pointsTotal); //draw the converted to ascii points array 
  lcd.string(75,145,300,220,RED,FONT4,TRANS,"TOUCH TO RESTART");   
  delay(1000);
  
  //wait for a touch on screen to restart
  while(lcd.touchScreen(touch)==0);
  moleCounter=20;                   //reset the moleCounter
  points=0;                         //reset points
  lcd.erase();                      //erase screen and restart all
 } 
}
