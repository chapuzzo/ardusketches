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

#define PENSIZE 5         //size of the drawing pen 

//Each time we use the touchscreen we must define a int array that stores the X and Y readed or touched coordinates.
int touch[2];
//Each time we use the touchicon we must define a char array that stores the name of the touched icon.
char icon[3];

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
}

void loop() { //main loop
    
    lcd.baudChange(2000000);                                      // Set a fast baud!, always that we use touch functions is recommended to use fast baud rates
    
    //front cover
    lcd.string(85,50,290,220,YELLOW,FONT7,TRANS,"Mini Paint");        
    lcd.string(45,95,290,220,BLUE,FONT5,TRANS,"Touch any icon to erase screen");
    lcd.string(30,160,310,220,MAGENTA,FONT4,TRANS,"Touch screen to begin");
    
    while(!lcd.touchScreen(touch));                                     // Wait for a touch on the screen to start
    lcd.erase();
    delay(500);
    
    while(1){                                                           // Loop forever
      if(lcd.touchScreen(touch)){                                       // If we receive a touch on the screen
        lcd.drawCircle(touch[XCOORD],touch[YCOORD],PENSIZE,GREEN,FILL); // Draw circle on touched coordinates
      }
      if(lcd.touchIcon(icon)){                                          // If we receive a touch on any icon
        lcd.erase();                                                    // Erase screen         
      }
    }
}
