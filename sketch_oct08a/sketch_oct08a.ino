#include <SMARTGPU.h>     //include the SMARTGPU library!

SMARTGPU lcd;             //create our object called LCD

char message[]="Hello World";
int buffer[2];
int prev[2]; 
int tm = 0;

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
  prev[0] = 0;
  prev[1] = 0;
}

boolean nearThan(int threshold, int a, int b){
  return abs(a-b) < threshold;
}

void loop() { //main loop
  //lcd.erase();   //erase screen
  if (lcd.touchScreen(buffer))
    {

      if (prev[0] != 0 && prev[1] != 0)
        lcd.drawLine(prev[0],prev[1],buffer[0],buffer[1],WHITE);
        
      //if (nearThan(5, prev[0],buffer[0]) && nearThan(5,prev[1],buffer[1])){      
      if (millis()-tm > 100)
      {
        prev[0]=0;
        prev[1]=0;
      }
      else {
        prev[0] = buffer[0];
        prev[1] = buffer[1];
      }
      tm = millis();
        
    }
    
    //lcd.putPixel(buffer[0],buffer[1],CYAN);                          //draw a pixel
  //lcd.drawCircle(buffer[0],buffer[1],3,RED,FILL);
  //lcd.drawLine(50,50,150,200,WHITE);                   //draw a line
  //lcd.drawRectangle(10,10,200,180,RED,UNFILL);         //draw a rectangle
  //lcd.drawCircle(160,120,50,GREEN,UNFILL);             //draw a circle
  //lcd.drawTriangle(15,15,200,210,180,70,BLUE,UNFILL);  //draw a triangle
  //lcd.putLetter(100,100,MAGENTA,FONT3,TRANS,'E');      //write a single letter 'E'
  //lcd.imageSD(0,0,"hydra320");                         //Open image "hydra320.bmp" stored on the microSD card
  //lcd.string(10,10,300,220,YELLOW,FONT3,TRANS,"String test for SMARTGPU");  //write a string on the screen
  //lcd.stringSD(5,50,300,230,MAGENTA,FONT3,TRANS,BEGINNING,ALLCONTENTS,"text1");  //call the text file "text1.txt" previously stored on the micro SD card
  //delay(1000);
}
