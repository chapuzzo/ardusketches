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

//miniSMARTGPU Command Execution responses definitions
#define OK                  0
#define DISK_ERROR          1
#define INT_ERROR           2
#define NOT_READY           3
#define NO_FILE             4
#define NO_PATH             5
#define INVALID_NAME        6
#define DENIED              7
#define ALREADY_EXIST       8
#define INVALID_OBJECT      9
#define WRITE_PROTECTED    10
#define INVALID_DRIVE      11
#define NOT_ENABLED        12
#define NO_FILE_SYSTEM     13
#define MAKE_FILE_ABORTED  14
#define TIMEOUT            15
#define LOCKED             16
#define NOT_ENOUGHT_CORE   17
#define TOO_MANY_FILES     18
#define INVALID_PARAMETER  19

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
	
	uint8_t touchRaw(uint8_t[]); //
	
	uint8_t calibrate(uint16_t , uint16_t , uint16_t , uint16_t );     //

	uint8_t	SDFgetNumberOfFiles(unsigned char*);
	
	uint8_t	SDFgetFileNumName(unsigned char, char[]);	

/****************************************************************/
//Those next functions return file execution status instead of ACK 'O' or NAK 'F'
/****************************************************************/
	
	uint8_t SDFopenFile(uint8_t, char[]);
	
	uint8_t SDFcloseFile();
	
	uint8_t SDFsaveFile();
	
	uint8_t SDFsetPointer(unsigned long);	

	uint8_t SDFreadFile(unsigned int, char[], unsigned int*);	

	uint8_t SDFwriteFile(unsigned int, char[], unsigned int*);
	
};

#endif
