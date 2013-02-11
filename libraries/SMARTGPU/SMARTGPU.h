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
 IMPORTANT : This library is created for the Arduino 1.0 Software IDE
********************************************************/

#ifndef SMARTGPU_h
#define SMARTGPU_h

#include <inttypes.h>

//General definitions
#define RESET 13
#define TX 1
#define RX 0
#define OFF 0
#define ON 1
#define FULL 127
#define UNFILL 0
#define FILL 1
#define TRANS 0
#define COLOUR 1
#define BEGINNING 0
#define ALLCONTENTS 0
#define LANDSCAPEL  0x00  //left
#define PORTRAITL   0x01  //low
#define LANDSCAPER  0x02  //right
#define PORTRAITT   0x03  //top
#define DOUT0 0
#define DOUT1 1
#define GND 0
#define VCC 1
#define XCOORD 0
#define YCOORD 1
#define WIDTH  320
#define HEIGHT 240

//basic colours definition
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F

//File access definitions
#define READONLY     0x01
#define WRITEONLY    0x02
#define READWRITE    0x03
#define CREATENEW    0x04
#define OPENALWAYS   0x10
#define CREATEALWAYS 0x08

//fonts definition
#define FONT0   0x00
#define FONT1   0x01
#define FONT2   0x02
#define FONT3   0x03
#define FONT4   0x04
#define FONT5   0x05
#define FONT6   0x06
#define FONT7   0x07

class SMARTGPU{
	
public:
    SMARTGPU();
	
	void init();

	void reset();
	
	uint8_t start();  

	uint8_t erase();

	uint8_t sleep(uint8_t);
	
	uint8_t orientation(uint8_t);
	
	uint8_t bright(uint8_t);
	
	uint8_t baudChange(unsigned long val);
	
	uint8_t digitalOut(uint8_t, uint8_t);
	
	uint8_t setScreenBackground(int);
	
	uint8_t setTextBackground(int);
	
	uint8_t memoryRead(int, int, int, int, char[]);
	
	uint8_t putPixel(int, int, int);
	
	uint8_t drawLine(int, int, int, int, int);
	
	uint8_t drawRectangle(int, int, int, int, int, uint8_t);
	
	uint8_t drawTriangle(int, int, int, int, int, int, int, uint8_t);
	
	uint8_t drawCircle(int, int, int, int, uint8_t);
	
	uint8_t putLetter(int, int, int, uint8_t, uint8_t, uint8_t);
	
	uint8_t string(int, int, int, int, int, uint8_t, uint8_t, char[]);
	
	uint8_t stringSD(int, int, int, int, int, uint8_t, uint8_t, int, int, char[]);
	
	uint8_t icon(int, int, int, int, char[]);
	
	uint8_t imageSD(int , int , char[]);
	
	uint8_t touchScreen(int[]);
	
	uint8_t touchIcon(char[]);

/****************************************************************/
//Those next functions return file execution status instead of ACK 'O' or NAK 'F'
/****************************************************************/
	
	uint8_t SDfopen(uint8_t, char[]);
	
	uint8_t SDfclose();
	
	uint8_t SDfsync();
	
	uint8_t SDfpointer(unsigned long);	

	uint8_t SDfread(unsigned int, char[], unsigned int*);	

	uint8_t SDfwrite(unsigned int, char[], unsigned int*);		
};

#endif
