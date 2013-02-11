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

char pixelArray[3];                     //Array to store the RGB888 pixel obtained with memoryRead()


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


void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop
    unsigned char penSize=1;
    int colPaint=BLACK;
    char pen[4]={'x','0','1',0x00};         //Array that show the current penSize
    
    lcd.baudChange(2000000);   // Set a fast baud!, always that we use touch functions is recommended to use fast baud rates
    
    //Load paint design
    lcd.imageSD(0,0,"paint");    
    lcd.string(7,54,48,65,GREEN,FONT1,FILL,"Erase");    //draw Erase word
    lcd.string(77,54,110,65,GREEN,FONT1,FILL,pen);      //draw penSize 
  
    while(1){   //Start the Paint application
    
      while(!lcd.touchScreen(touch));                   //Wait for a touch on the screen to do something      
      //Once we get a touch somewhere on the screen:
      if((touch[YCOORD]-penSize)<67){                   //the touch was on the menu
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
        lcd.drawCircle(touch[XCOORD],touch[YCOORD],penSize,colPaint,FILL);                    //Draw
      }
    }
}
