/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2013.
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


//Defines for the Horizontal Slider
#define SLH_X_START      100  //Slider start left coordinate
#define SLH_Y_START       20  //Slider start top coordinate
#define SLH_WIDTH        200  //Slider width size in pixels
#define SLH_HEIGHT        50  //Slider height size in pixels

//Defines for the Vertical Slider
#define SLV_X_START       20  //Slider start left coordinate
#define SLV_Y_START       20  //Slider start top coordinate
#define SLV_WIDTH         50  //Slider width size in pixels
#define SLV_HEIGHT       200  //Slider height size in pixels

boolean inside(int *pos, int x0, int y0, int x1, int y1){
  lcd.putPixel(pos[XCOORD],pos[YCOORD],0x8888);
  lcd.
  if ( (pos[XCOORD] > x0) &&
       (pos[YCOORD] > y0) &&
       (pos[XCOORD] < x1) &&
       (pos[YCOORD] < y1))
    return true;
  return false;
  
  
}


/**************************************************/
void updateHorizontalBar(unsigned int slValue){ //updates/draws a #defined horizontal bar with the received value from 0 - SLH_WIDTH
  if(slValue > SLH_WIDTH) slValue = SLH_WIDTH; //if received value is bigger, correct
  //draw the slider WHITE corner, we substract 1 and add 1 to make it a little bigger than the desired slider size
  lcd.drawRectangle(SLH_X_START -1, SLH_Y_START -1, SLH_X_START + SLH_WIDTH +1, SLH_Y_START + SLH_HEIGHT +1, WHITE, UNFILL);
  //erase the slider - BLACK
  lcd.drawRectangle(SLH_X_START, SLH_Y_START, SLH_X_START + SLH_WIDTH, SLH_Y_START + SLH_HEIGHT, BLACK, FILL);    
  //draw the current slider value - GREEN
  lcd.drawRectangle(SLH_X_START, SLH_Y_START, SLH_X_START + slValue, SLH_Y_START + SLH_HEIGHT, GREEN, FILL);       
}

/**************************************************/
void updateVerticalBar(unsigned int slValue){ //updates/draws a #defined vertical bar with the received value from 0 - SLV_HEIGHT
  if(slValue > SLV_HEIGHT) slValue = SLV_HEIGHT; //if received value is bigger, correct  
  //draw the slider WHITE corner, we substract 1 and add 1 to make it a little bigger than the desired slider size
  lcd.drawRectangle(SLV_X_START -1, SLV_Y_START -1, SLV_X_START + SLV_WIDTH +1, SLV_Y_START + SLV_HEIGHT +1, WHITE, UNFILL);
  //erase the slider - BLACK
  lcd.drawRectangle(SLV_X_START, SLV_Y_START, SLV_X_START + SLV_WIDTH, SLV_Y_START + SLV_HEIGHT, BLACK, FILL);  
  //draw the current slider value - YELLOW
  lcd.drawRectangle(SLV_X_START, SLV_Y_START + SLV_HEIGHT - slValue, SLV_X_START + SLV_WIDTH, SLV_Y_START + SLV_HEIGHT, YELLOW, FILL);      
}

/**************************************************/
unsigned char getHorizontalSlide(unsigned int *sliderValue){ //Ask for a touch on a defined horizontal slider, returns 1 if touch is present, returns 0 if not
  //Ask for touch
  lcd.touchScreen(touch);
  
  //Check if the touch was inside the slider rectangle
  //(touch[XCOORD] > SLH_X_START) && (touch[YCOORD] > SLH_Y_START) && (touch[XCOORD] < (SLH_X_START + SLH_WIDTH)) && (touch[YCOORD] < (SLH_Y_START + SLH_HEIGHT)
  if(inside(touch, SLH_X_START, SLH_Y_START, SLH_X_START + SLH_WIDTH, SLH_Y_START + SLH_HEIGHT)){ 
    //Now that we know that the touch was inside slider: 

    //---------------------------------------------------------------------------------------
    //This option updates SliderValue instantly with the new touched point value
    *sliderValue = touch[XCOORD] - SLH_X_START;    //update sliderValue variable with the new touched value    
        
//    //---------------------------------------------------------------------------------------
//    //This option updates SliderValue 1 by 1 steps until it reach touching position, instead of instantly slider change value
//    //now that we know that the touch is inside slider, check if we must increase or decrease value
//    if(touch[XCOORD] < SLH_X_START + sliderValue){ //if received touch XCOORD is smaller than current sliderValue
//      sliderValue--;                              //decrease sliderValue variable one step
//      if(sliderValue < 0) sliderValue = 0;
//    }else{                                        //received touch XCOORD is bigger than current sliderValue
//      sliderValue++;                              //increase sliderValue variable one step
//      if(sliderValue > SLH_WIDTH) sliderValue = SLH_WIDTH;
//    }    
    return 1;
  }
 return 0;
}

/**************************************************/
unsigned char getVerticalSlide(unsigned int *sliderValue){ //Ask for a touch on a defined verical slider, returns 1 if touch is present, returns 0 if not
  //Ask for touch
  lcd.touchScreen(touch);
  
  //Check if the touch was inside the slider rectangle
//  if((touch[XCOORD] > SLV_X_START) && (touch[YCOORD] > SLV_Y_START) && (touch[XCOORD] < (SLV_X_START + SLV_WIDTH)) && (touch[YCOORD] < (SLV_Y_START + SLV_HEIGHT))){ 
  if(inside(touch, SLV_X_START, SLV_Y_START, SLV_X_START + SLV_WIDTH, SLV_Y_START + SLV_HEIGHT)){ 

    //Now that we know that the touch was inside slider:

    //---------------------------------------------------------------------------------------
    //This first option updates SliderValue instantly with the new touched point value
    *sliderValue = SLV_Y_START + SLV_HEIGHT - touch[YCOORD];    //update sliderValue variable with the new touched value    
        
//    //---------------------------------------------------------------------------------------
//    //This second option updates SliderValue 1 by 1 steps until it reach touching position, instead of instantly slider change value
//    //now that we know that the touch is inside slider, check if we must increase or decrease value
//    if(touch[YCOORD] < (SLV_Y_START + SLV_HEIGHT - sliderValue)){ //if received touch YCOORD is smaller than current sliderValue
//      sliderValue++;                              //increase sliderValue variable one step      
//      if(sliderValue > SLV_HEIGHT) sliderValue = SLV_HEIGHT;      
//    }else{                                        //received touch YCOORD is bigger than current sliderValue
//      sliderValue--;                              //decrease sliderValue variable one step
//      if(sliderValue < 0) sliderValue = 0;      
//    }    
    return 1;
  }
 return 0;
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
  unsigned int horizontalSlideValue=0, verticalSlideValue=0;
  
  lcd.baudChange(1000000);         //set high baud for advanced applications
  
  //draw bars with initial values(zeros)
  updateHorizontalBar(0);
  updateVerticalBar(0);
  
  while(1){
    //Ask for touch on horizontal slider
    if(getHorizontalSlide(&horizontalSlideValue) ==1){ //if touch on Horizontal Slider is valid
      //now that we know that a touch was on the horizontal slide:
      while (getHorizontalSlide(&horizontalSlideValue) ==1);
      updateHorizontalBar(horizontalSlideValue);    
      //Perform something else with horizontalSlideValue      
    }
    //Ask for touch on vertical slider    
    if(getVerticalSlide(&verticalSlideValue) ==1){  //if touch on Vertical Slider is valid
      //now that we know that a touch was on the horizontal slide:
      while(getVerticalSlide(&verticalSlideValue) ==1);
      updateVerticalBar(verticalSlideValue);    
      //Perform something else with verticalSlideValue  
    }    
  }  
}

