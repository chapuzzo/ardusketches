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

//Each time we use the touchscreen we must define a int array that stores the X and Y readed or touched coordinates.
int touch[2];
//Each time we use the touchicon we must define a char array that stores the name of the touched icon.
char icon[3];


char imagesOnSDCard[8][9]={"Peng320","Koala320","Hydra320","Lig320","Sea320","Tul320","Des320","Flow320"}; //array containing the names of the different called images


void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop
  char pic;
  
  lcd.baudChange(500000);                 // Set a fast baud!, always that we use touch functions is recommended to use fast baud rates

  while(1){   //Loop forever in the slide show!
    lcd.imageSD(0,0,imagesOnSDCard[pic]); //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.imageSD(3,219,"prev");            //Load the prev icon        
    lcd.imageSD(300,219,"next");          //Load the next icon
       
    while(!lcd.touchScreen(touch));       //Wait for a touch on the screen to show next or previous picture
    
    //check if we go to the next image, or to the previous one
    if(touch[XCOORD]>160){                //if the received touch was on the right middle of the screen we advance the image, else we decrease and go to previous image
      pic++;                              //decrease image selector
      if(pic>7){                          //if we reach the position of the last image, we restart to image 0
        pic=0;                 
      }        
    }else{
      pic--;    
      if(pic<0){                          //if we reach the position of the first image, we move to image 7
        pic=7;  
      }    
    }   
  }
}
