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

//THIS SKETCH NEEDS THE SMARTGPU Arduino library V4

/********************************************************
 This simple sketch does the next:
 1.- list/count the files
 2.- print the number of files
 3.- print the names while they fit
********************************************************/

#include <SMARTGPU.h>     //include the SMARTGPU library!

#define s Serial          // this allows to use Serial mapped to Serial1 in Leonardo,
                          // while also using Serial (as s) for pc communication.

SMARTGPU lcd;             //create our object called lcd

unsigned int row=5;

/**************************************************/
/**************************************************/
//Initial setup
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
  while(!s);
  s.begin(9600);
  lcd.baudChange(2000000); //set high baudrate
}

/**************************************************/
/****************** MAIN LOOP *********************/
/**************************************************/
/**************************************************/
void loop() { //main loop
    row = 5;
    s.println(millis());
    char buffer[100]={0}; //working buffer
    unsigned char files=0, i=0;
    char milis[50];  

    
        
    //print
    lcd.string(10,row,319,239, GREEN, FONT2, UNFILL, "List files + print names demo!"); row+=20; 
  delay(100);    
    lcd.string(10,row,319,239, GREEN, FONT2, UNFILL, "List Dirs and Files...");             row+=15;
    lcd.SDFgetNumberOfFiles(&files);    //obtain Number of Files
    lcd.string(10,row,319,239, GREEN, FONT2, UNFILL, "Files:");    
    itoa(files,buffer,10);                      //convert the number to ascii/string
    lcd.string(70,row,319,239, GREEN, FONT2, UNFILL, buffer);   row+=15; 

    //print file names
    lcd.string(10,row,319,239, GREEN, FONT2, UNFILL, "    File Names");             row+=10;
    lcd.string(10,row,319,239, GREEN, FONT2, UNFILL, "--------------------");             row+=10;
    for(i=1;i<files;i++){
      lcd.SDFgetFileNumName(i,buffer); //get Dir number i name in buffer
      lcd.string(10,row,319,239, GREEN, FONT2, FILL, buffer);// row+=10;      //print the name if fit
      //if(row>230)break; //if name wont fit
          lcd.string(190, row, 319, 239, RED, FONT2, FILL, "x");
         sprintf(milis, "%lu", millis());
          lcd.string(200, row, 319, 239, RED, FONT2, FILL, milis);
          //delay(100);
        row += 10;  
 
    }
    
    //while(1); //loop forever    
    //delay(300);
}
