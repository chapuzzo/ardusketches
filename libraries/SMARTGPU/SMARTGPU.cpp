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

//SMARTGPU Arduino Library V4

/********************************************************
 IMPORTANT : This library is created for the Arduino 1.0 Software IDE
********************************************************/

#include <avr/interrupt.h>
#include <Arduino.h> 
	
#include "SMARTGPU.h"

#ifdef __AVR_ATmega32U4__
#define Serial Serial1
#endif

// SMART GPU DEFAULT BAUD RATE: 9600bps

SMARTGPU::SMARTGPU(){
	init();
}

/********** high level commands, for the user! */
void SMARTGPU::init(){      //configure the arduino board for SMARTGPU board
	analogReference(EXTERNAL); 
	Serial.begin (9600);	
	pinMode(TX,OUTPUT);
	pinMode(RX,INPUT);
	pinMode(RESET, OUTPUT); 
	digitalWrite(RESET, HIGH);   // set the pin to 5v to avoid reset 
}
 
void SMARTGPU::reset(){          //Reset the SMARTGPU board
	digitalWrite(RESET, LOW);    // set the pin to GND to reset 
	delay(500);
	digitalWrite(RESET, HIGH);   // set the pin to 5v to end reset
	delay(500);	
}

uint8_t SMARTGPU::start(){       //Init the SMARTGPU
  delay(500); 
  Serial.write('U');  
  while(Serial.available() == 0); 
  delay(2000);
  return Serial.read();
}

uint8_t SMARTGPU::erase(){       //Erase the SMARTGPU screen
  Serial.write('E'); 
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::sleep(uint8_t mode){       //Send SMARTGPU to sleep mode
  Serial.write('Z'); 
  Serial.write(mode);
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::orientation(uint8_t side){       //Change display orientation
  Serial.write('O'); 
  Serial.write(side);
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::bright(uint8_t val){       //Change display brightness
  Serial.write('V'); 
  Serial.write(val);
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::baudChange(unsigned long val){       //Change baud rate of arduino and SMARTGPU board
  uint8_t aux;
 
  switch(val){
	case 9600:
	  aux=0;
	break;
	case 19200:
	  aux=1;
	break;
	case 57600:
	  aux=2;
	break;
	case 115200:
	  aux=3;
	break;
	case 256000:
	  aux=4;
	break;	
	case 500000:
	  aux=5;
	break;
	case 1000000:
	  aux=6;
	break;
	case 2000000:
	  aux=7;
	break;
	default:
	  return 'F';
	break;
  } 
  Serial.write('X');
  Serial.write(aux);
  while(Serial.available() == 0);  
  aux=Serial.read();
  if(aux=='O'){
	Serial.end();
	delay(150);
	Serial.begin(val);
	delay(200);
	while(Serial.available() == 0);  
	return Serial.read();
  }else{
	return aux;
  }
}

uint8_t SMARTGPU::digitalOut(uint8_t number, uint8_t val ){       //Set Digital out pins to a logic value
  Serial.write('D'); 
  Serial.write(number);
  Serial.write(val);
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::setScreenBackground(int colour){       //Change the default screen background colour for erase function
  Serial.write('B'); 
  Serial.write(colour>>8);
  Serial.write(colour); 
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::setTextBackground(int colour){       //Set the default text background colour for letters and strings
  Serial.write('A'); 
  Serial.write(colour>>8);
  Serial.write(colour); 
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::memoryRead(int x1, int y1, int x2, int y2, char buffer[]){ //Read the internal memory of the SMARTGPU, This command returns 24bit pixels (3 bytes)
  unsigned int i,j,k=0;
  
  Serial.write('M'); 
  Serial.write(x1>>8); 
  Serial.write(x1);
  Serial.write(y1>>8);
  Serial.write(y1);
  Serial.write(x2>>8); 
  Serial.write(x2);
  Serial.write(y2>>8);
  Serial.write(y2); 

  while(Serial.available() == 0);//wait for pixels
  //receive all the pixels
  for(j=0;j<=(y2-y1);j++){
	for(i=0;i<=(x2-x1);i++){
		while(Serial.available() == 0);	
		buffer[k]=Serial.read(); //Red
		k++;
		while(Serial.available() == 0);	
		buffer[k]=Serial.read(); //Green
		k++;
		while(Serial.available() == 0);			
		buffer[k]=Serial.read(); //Blue
		k++;
	}	
  }
  while(Serial.available() == 0);  
  return Serial.read();  
}

uint8_t SMARTGPU::putPixel(int x, int y, int colour){       //Draw a pixel on the screen
  Serial.write('P'); 
  Serial.write(x>>8); 
  Serial.write(x);
  Serial.write(y>>8);
  Serial.write(y);
  Serial.write(colour>>8);
  Serial.write(colour);
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::drawLine(int x1, int y1, int x2, int y2, int colour){       //Draw a line on the screen
  Serial.write('L'); 
  Serial.write(x1>>8); 
  Serial.write(x1);
  Serial.write(y1>>8);
  Serial.write(y1);
  Serial.write(x2>>8); 
  Serial.write(x2);
  Serial.write(y2>>8);
  Serial.write(y2);  
  Serial.write(colour>>8);
  Serial.write(colour);
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::drawRectangle(int x1, int y1, int x2, int y2, int colour, uint8_t fill){       //Draw a rectangle on the screen
  Serial.write('R'); 
  Serial.write(x1>>8); 
  Serial.write(x1);
  Serial.write(y1>>8);
  Serial.write(y1);
  Serial.write(x2>>8); 
  Serial.write(x2);
  Serial.write(y2>>8);
  Serial.write(y2);  
  Serial.write(colour>>8);
  Serial.write(colour);
  Serial.write(fill);  
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int colour, uint8_t fill){       //Draw a triangle on the screen
  Serial.write('T'); 
  Serial.write(x1>>8); 
  Serial.write(x1);
  Serial.write(y1>>8);
  Serial.write(y1);
  Serial.write(x2>>8); 
  Serial.write(x2);
  Serial.write(y2>>8);
  Serial.write(y2);  
  Serial.write(x3>>8); 
  Serial.write(x3);
  Serial.write(y3>>8);
  Serial.write(y3);    
  Serial.write(colour>>8);
  Serial.write(colour);
  Serial.write(fill);  
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::drawCircle(int x, int y, int radius, int colour, uint8_t fill){       //Draw a circle on the screen
  Serial.write('C'); 
  Serial.write(x>>8); 
  Serial.write(x);
  Serial.write(y>>8);
  Serial.write(y);
  Serial.write(radius>>8);
  Serial.write(radius);
  Serial.write(colour>>8);
  Serial.write(colour);
  Serial.write(fill);  
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::putLetter(int x, int y, int colour, uint8_t font, uint8_t fill, uint8_t letter){       //Draw a letter on the screen
  
  Serial.write('W'); 
  Serial.write(x>>8); 
  Serial.write(x);
  Serial.write(y>>8);
  Serial.write(y);
  Serial.write(colour>>8);
  Serial.write(colour);
  Serial.write(font); 
  Serial.write(fill); 
  Serial.write(letter); 
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::string(int x1, int y1, int x2, int y2, int colour, uint8_t font, uint8_t fill, char text[]){       //Draw a string on the screen
  int counter=0;
  
  Serial.write('S'); 
  Serial.write('N'); //not SD
  Serial.write(x1>>8); 
  Serial.write(x1);
  Serial.write(y1>>8);
  Serial.write(y1);
  Serial.write(x2>>8); 
  Serial.write(x2);
  Serial.write(y2>>8);
  Serial.write(y2);  
  Serial.write(colour>>8);
  Serial.write(colour);
  Serial.write(font); 
  Serial.write(fill); 
  while(1){
	Serial.write(text[counter]);
    if(text[counter]==0x00){
      break;
	}	
	counter++;
  }
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::stringSD(int x1, int y1, int x2, int y2, int colour, uint8_t font, uint8_t fill, int BS, int BR, char name[]){       //Draw a String from a text file contained on the micro SD card on the screen
  uint8_t counter=0;
  
  Serial.write('S'); 
  Serial.write('S'); //from SD
  Serial.write(x1>>8); 
  Serial.write(x1);
  Serial.write(y1>>8);
  Serial.write(y1);
  Serial.write(x2>>8); 
  Serial.write(x2);
  Serial.write(y2>>8);
  Serial.write(y2);  
  Serial.write(colour>>8);
  Serial.write(colour);
  Serial.write(font); 
  Serial.write(fill); 
  Serial.write(BS>>8);
  Serial.write(BS);  
  Serial.write(BR>>8);
  Serial.write(BR);  
  while(1){
	Serial.print(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::icon(int x1, int y1, int x2, int y2, char icon[]){            //Send and image or icon pixel by pixel to SMARTGPU, 16bit(2 bytes) each pixel RGB565
  unsigned int i,j,k=0; 
  
  Serial.write('I'); 
  Serial.write('N'); //not SD
  Serial.write(x1>>8); 
  Serial.write(x1);
  Serial.write(y1>>8);
  Serial.write(y1);
  Serial.write(x2>>8); 
  Serial.write(x2);
  Serial.write(y2>>8);
  Serial.write(y2);
  
  //Send icon buffer pixel by pixel
  for(j=0;j<=(y2-y1);j++){
	for(i=0;i<=(x2-x1);i++){
		Serial.write(icon[k]);
	    k++;
	}
  }
  while(Serial.available() == 0);  
  return Serial.read();  
}

uint8_t SMARTGPU::imageSD(int x, int y, char name[]){        //Draw an Image contained on the micro SD card on the screen, top left corner coordinates
  uint8_t counter=0;
  
  Serial.write('I'); 
  Serial.write('S'); //from SD
  Serial.write(x>>8); 
  Serial.write(x);
  Serial.write(y>>8);
  Serial.write(y);
  while(1){
	Serial.write(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  while(Serial.available() == 0);  
  return Serial.read();
}

uint8_t SMARTGPU::touchScreen(int buffer[]){          //Ask for a touch on the screen, if return=1, touch coordinates are stored on the buffer[]
  
  Serial.write('G');
  while(Serial.available() < 5);
  buffer[0]=Serial.read();
  buffer[0]=buffer[0]<<8;
  buffer[0]|=Serial.read();
  buffer[1]=Serial.read();
  buffer[1]=buffer[1]<<8;
  buffer[1]|=Serial.read();
  Serial.read();  
  if(buffer[0]<0x0200){
	return 1;
  }else{
    return 0;
  }
}

uint8_t SMARTGPU::touchIcon(char buffer[]){          //Ask for a touch on the icons of the screen, if return=1, icon name is stored on the buffer[]
  
  Serial.write('G');
  while(Serial.available() < 5);
  buffer[0]=Serial.read();
  buffer[1]=Serial.read();
  buffer[2]=Serial.read();
  buffer[3]=Serial.read();
  Serial.read();  
  if(!(buffer[0]<0x02) & (buffer[0]!=0x4E)){
	return 1;
  }else{
    return 0;
  }
}

uint8_t SMARTGPU::touchRaw(uint8_t buffer[]){        //Ask for touch, wherever it is, always returns 1  
    Serial.write('G');
  while(Serial.available() < 5);
  buffer[0]=Serial.read();
  buffer[1]=Serial.read();
  buffer[2]=Serial.read();
  buffer[3]=Serial.read();
  buffer[4]=0;
  Serial.read();
  if (buffer[0] == 'N') return 0;
  return 1;
}

uint8_t SMARTGPU::calibrate(uint16_t xsub, uint16_t ysub, uint16_t xdiv, uint16_t ydiv){       //
  Serial.write('K'); 
  Serial.write('U'); 
  Serial.write(xsub>>8); 
  Serial.write(xsub);
  Serial.write(ysub>>8);
  Serial.write(ysub);
  Serial.write(xdiv>>8); 
  Serial.write(xdiv);
  Serial.write(ydiv>>8);
  Serial.write(ydiv);  
  Serial.write('W');
  while(Serial.available() == 0);  
  return Serial.read();
}


uint8_t SMARTGPU::SDFgetNumberOfFiles(unsigned char *numOfFiles){
  unsigned char fileCounter=0, data=0, aux=0;
  
  delay(1);    
  Serial.write('H'); //List Files to get number of files
  do{
	while(Serial.available()==0);
	data=Serial.read(); 
	if(data==',') fileCounter++; //if we find a comma then we increase file counter	
  }while(data!=0x00);

  *numOfFiles=fileCounter;
  
  while(Serial.available()==0);  
  aux= Serial.read();
  return aux;
}

uint8_t SMARTGPU::SDFgetFileNumName(unsigned char fileNumber, char buffer[]){ //searches for the "fileNumber" parameter(must be different than zero) on the file list and updates the buffer with the file name ended with NULL character
  unsigned char fileCounter=0, data=0, aux=0, i=1, j=0;
  
  delay(1);    
  Serial.write('H'); //List Files to get number of files
  do{
	while(Serial.available() == 0);  
	data=Serial.read(); 
	if(data==',') fileCounter++; //if we find a comma then we increase file counter	
  }while(data!=0x00);
  
  while(Serial.available() == 0);  
  if(Serial.read()!='O') return 'F'; 
  
  while(Serial.available() != 0) Serial.read(); //flush RX buffer
  
  if((fileNumber>fileCounter) | fileNumber == 0x00){//if the requested file name is invalid(0x00) or is bigger than available number of files
	return 0x13; //invalid parameter   
  }

  delay(10);    
  Serial.write('H'); //List Files  

  while(i<fileNumber){
	while(Serial.available() == 0);  
	if(Serial.read()==',') i++; //if we find a comma then we increase i
  }
  while(1){
	while(Serial.available() == 0);  
	data=Serial.read(); 
	if(data==',') break; //if we find a comma then we break
    buffer[j++]=data;	
  }
  while(Serial.read()!=0x00); //wait until we receive all the rest of file names  
  aux=Serial.read(); //save response
  buffer[j]=0x00; //add the NULL character to the file Name
  return aux;
}

/****************************************************************/
//Those next functions return file execution status instead of ACK 'O' or NAK 'F'
/****************************************************************/

uint8_t SMARTGPU::SDFopenFile(uint8_t mode, char name[]){
  uint8_t counter=0;
  uint8_t aux = 0;
  
  delay(100);
  Serial.write('F'); //memory card file management
  Serial.write('O'); //file open
  Serial.write(mode);
  while(1){
	Serial.write(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  
  while(Serial.available() < 2);  
  aux= Serial.read();
  Serial.read();
  return aux;
}

uint8_t SMARTGPU::SDFcloseFile(){
  uint8_t aux = 0;

  delay(50);
  Serial.write('F'); //memory card file management
  Serial.write('C'); //file close
  
  while(Serial.available() < 2);
  aux= Serial.read();
  Serial.read();
  return aux;  
}

uint8_t SMARTGPU::SDFsaveFile(){
  uint8_t aux = 0;
  
  Serial.write('F'); //memory card file management
  Serial.write('S'); //file sync
  
  while(Serial.available() < 2);
  aux= Serial.read();
  Serial.read();
  return aux;  
}

uint8_t SMARTGPU::SDFsetPointer(unsigned long position){ //moves the file read/write pointer to the provided position parameter
  uint8_t aux = 0;
  
  Serial.write('F'); //memory card file management
  Serial.write('P'); //file sync
  Serial.write(position>>24);
  Serial.write(position>>16);
  Serial.write(position>>8);
  Serial.write(position);
   
  while(Serial.available() < 2);
  aux= Serial.read();
  Serial.read();
  return aux;  
}	

uint8_t SMARTGPU::SDFreadFile(unsigned int BTR, char buffer[], unsigned int *SRB){ //Bytes to Read, Read Buffer, Succesfully Read Bytes
  uint8_t aux = 0;
  unsigned int x=0, sr=0;

  Serial.write('F'); //memory card file management
  Serial.write('R'); //file read
  Serial.write(BTR>>8);
  Serial.write(BTR);  
  for(x=0;x<BTR;x++){
	while(Serial.available() == 0);  
	buffer[x]=Serial.read();
  }
  while(Serial.available() < 4);  
  sr=Serial.read();
  sr=sr<<8;
  sr|=Serial.read();
  
  aux= Serial.read();
  Serial.read();
  *SRB = sr;  
  return aux;  
}	

uint8_t SMARTGPU::SDFwriteFile(unsigned int BTW, char buffer[], unsigned int *SWB){ //Bytes to Write, Write Buffer, Succesfully Written Bytes
  uint8_t aux = 0;
  unsigned int x=0, sw=0;

  delay(10);  
  Serial.write('F'); //memory card file management
  Serial.write('W'); //file write
  Serial.write(BTW>>8);
  Serial.write(BTW);    
  for(x=0;x<BTW;x++){
	Serial.write(buffer[x]);
  }
  while(Serial.available() < 4);  
  sw=Serial.read();
  sw=sw<<8;
  sw|=Serial.read();

  while(Serial.available() < 2);  
  aux= Serial.read();
  Serial.read();
  *SWB = sw;   
  return aux;   
}

