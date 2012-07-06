#include <botonera.h>
extern boton_t botonera;

/*#include <SdFat.h>
Sd2Card card;*/
/**********************************************
Define zone
**********************************************/
#define RS 19
#define WR 18
#define CS 17
#define RST 16

#define T_CLK 15
#define T_CS 20
#define T_DIN 14
#define T_DOUT 8
#define T_IRQ 9

#define X_CONST 240
#define Y_CONST 320

#define PREC_TOUCH_CONST 25

#define PixSizeX	13.78
#define PixOffsX	411

#define PixSizeY	11.01
#define PixOffsY	378

#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write

/* LCD color */
#define White       0xFFFF
#define Black        0x0000
#define Blue         0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

/**********************************************
Val Zone
**********************************************/
int TP_X,TP_Y;

/**********************************************
Standard C functions zone
**********************************************/
void Write_Command(unsigned int c)
{
        digitalWrite(RS,LOW);//LCD_RS=0; 
	digitalWrite(CS,LOW);//LCD_CS =0;	 
	PORTD = c>>8; //LCD_DataPortH=DH>>8;
	digitalWrite(WR,LOW);//LCD_WR=0;
	digitalWrite(WR,HIGH);//LCD_WR=1;	
	PORTD = c;//LCD_DataPortH=DH;		
	digitalWrite(WR,LOW);//LCD_WR=0;
	digitalWrite(WR,HIGH);//LCD_WR=1;
	digitalWrite(CS,HIGH);//LCD_CS =0;
}

void Write_Data(unsigned int c)
{
        digitalWrite(RS,HIGH);//LCD_RS=0;
	digitalWrite(CS,LOW);//LCD_CS =0;	 
	PORTD = c>>8; //LCD_DataPortH=DH>>8;
	digitalWrite(WR,LOW);//LCD_WR=0;
	digitalWrite(WR,HIGH);//LCD_WR=1;	
	PORTD = c;//LCD_DataPortH=DH;		
	digitalWrite(WR,LOW);//LCD_WR=0;
	digitalWrite(WR,HIGH);//LCD_WR=1;
	digitalWrite(CS,HIGH);//LCD_CS =0;
}

void Write_Command_Data(unsigned int cmd,unsigned int dat)
{
	Write_Command(cmd);
	Write_Data(dat);
}

void Lcd_Init()
{
	pinMode(RS,OUTPUT);
	pinMode(WR,OUTPUT);
	pinMode(CS,OUTPUT);
	pinMode(RST,OUTPUT);
	
	DDRD = 0xFF;
  
	digitalWrite(RST,HIGH);
        delay(1);	
	digitalWrite(RST,LOW);
	delay(1);
	
	digitalWrite(RST,HIGH);
	digitalWrite(CS,HIGH);
	digitalWrite(WR,HIGH);
	delay(20);

	
	Write_Command_Data(0x0001,0x0100); 
	Write_Command_Data(0x0002,0x0700); 
	Write_Command_Data(0x0003,0x1030); 
	Write_Command_Data(0x0004,0x0000); 
	Write_Command_Data(0x0008,0x0207);  
	Write_Command_Data(0x0009,0x0000);
	Write_Command_Data(0x000A,0x0000); 
	Write_Command_Data(0x000C,0x0000); 
	Write_Command_Data(0x000D,0x0000);
	Write_Command_Data(0x000F,0x0000);
	//power on sequence VGHVGL
	Write_Command_Data(0x0010,0x0000);   
	Write_Command_Data(0x0011,0x0007);  
	Write_Command_Data(0x0012,0x0000);  
	Write_Command_Data(0x0013,0x0000); 
	//vgh 
	Write_Command_Data(0x0010,0x1290);   
	Write_Command_Data(0x0011,0x0227);
	//delays(100);
	//vregiout 
	Write_Command_Data(0x0012,0x001d); //0x001b
	//delays(100); 
	//vom amplitude
	Write_Command_Data(0x0013,0x1500);
	//delays(100); 
	//vom H
	Write_Command_Data(0x0029,0x0018); 
	Write_Command_Data(0x002B,0x000D); 

	//gamma
	Write_Command_Data(0x0030,0x0004);
	Write_Command_Data(0x0031,0x0307);
	Write_Command_Data(0x0032,0x0002);// 0006
	Write_Command_Data(0x0035,0x0206);
	Write_Command_Data(0x0036,0x0408);
	Write_Command_Data(0x0037,0x0507); 
	Write_Command_Data(0x0038,0x0204);//0200
	Write_Command_Data(0x0039,0x0707); 
	Write_Command_Data(0x003C,0x0405);// 0504
	Write_Command_Data(0x003D,0x0F02); 
	//ram
	Write_Command_Data(0x0050,0x0000); 
	Write_Command_Data(0x0051,0x00EF);
	Write_Command_Data(0x0052,0x0000); 
	Write_Command_Data(0x0053,0x013F);  
	Write_Command_Data(0x0060,0xA700); 
	Write_Command_Data(0x0061,0x0001); 
	Write_Command_Data(0x006A,0x0000); 
	//
	Write_Command_Data(0x0080,0x0000); 
	Write_Command_Data(0x0081,0x0000); 
	Write_Command_Data(0x0082,0x0000); 
	Write_Command_Data(0x0083,0x0000); 
	Write_Command_Data(0x0084,0x0000); 
	Write_Command_Data(0x0085,0x0000); 
	//
	Write_Command_Data(0x0090,0x0010); 
	Write_Command_Data(0x0092,0x0600); 
	Write_Command_Data(0x0093,0x0003); 
	Write_Command_Data(0x0095,0x0110); 
	Write_Command_Data(0x0097,0x0000); 
	Write_Command_Data(0x0098,0x0000);
	Write_Command_Data(0x0007,0x0133);
}
void SetXY(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
  Write_Command_Data(WINDOW_XADDR_START,x0);
  Write_Command_Data(WINDOW_XADDR_END,x1);
  Write_Command_Data(WINDOW_YADDR_START,y0);
  Write_Command_Data(WINDOW_YADDR_END,y1);
  Write_Command_Data(GRAM_XADDR,x0);
  Write_Command_Data(GRAM_YADDR,y0);
  Write_Command (0x0022);//LCD_WriteCMD(GRAMWR);
}


void Pant(unsigned int color)
{
	int i,j;
	SetXY(0,240,0,320);

    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
         Write_Data(color);
	    }

	  }		
}
void LCD_clear()
{
    unsigned int i,j;
	SetXY(0,240,0,320);
	for(i=0;i<X_CONST;i++)
	{
	    for(j=0;j<Y_CONST;j++)
		{    
          	Write_Data(Blue2);
		}
	}
}

void Touch_Init(void)
{
	pinMode(T_CLK,  OUTPUT);
    pinMode(T_CS,   OUTPUT);
    pinMode(T_DIN,  OUTPUT);
    pinMode(T_DOUT, INPUT);
    pinMode(T_IRQ,  INPUT);

	digitalWrite(T_CS,  HIGH);
	digitalWrite(T_CLK, HIGH);
	digitalWrite(T_DIN, HIGH);
	digitalWrite(T_CLK, HIGH);
}

void Touch_WriteData(unsigned char data)
{
	unsigned char temp;
	unsigned char nop;
	unsigned char count;

	temp=data;
	digitalWrite(T_CLK,LOW);

	for(count=0; count<8; count++)
	{
		if(temp & 0x80)
			digitalWrite(T_DIN, HIGH);
		else
			digitalWrite(T_DIN, LOW);
		temp = temp << 1; 
		digitalWrite(T_CLK, LOW);                
		nop++;
		digitalWrite(T_CLK, HIGH);
		nop++;
	}
}

unsigned int Touch_ReadData()
{
	unsigned char nop;
	unsigned int data = 0;
	unsigned char count;
	for(count=0; count<12; count++)
	{
		data <<= 1;
		digitalWrite(T_CLK, HIGH);               
		nop++;
		digitalWrite(T_CLK, LOW);
		nop++;
		if (digitalRead(T_DOUT))
			data++;
	}
	return(data);
}
void Touch_Read()
{
	unsigned long tx=0;
	unsigned long ty=0;

	digitalWrite(T_CS,LOW);                    

	for (int i=0; i<PREC_TOUCH_CONST; i++)
	{
		Touch_WriteData(0x90);        
		digitalWrite(T_CLK,HIGH);
		digitalWrite(T_CLK,LOW); 
		ty+=Touch_ReadData();

		Touch_WriteData(0xD0);      
		digitalWrite(T_CLK,HIGH);
		digitalWrite(T_CLK,LOW);
		tx+=Touch_ReadData();
	}

	digitalWrite(T_CS,HIGH);

	TP_X=tx/PREC_TOUCH_CONST;
	TP_Y=ty/PREC_TOUCH_CONST;
}

char Touch_DataAvailable()
{
  char avail;
  avail = !digitalRead(T_IRQ);
  return avail;
}

int Touch_GetX()
{
	int value;
	value = 240-((TP_X-PixOffsX)/PixSizeX);
	if (value < 0)
		value = 0;
	return value;
}
int Touch_GetY()
{
	int value;
	value = 320-((TP_Y-PixOffsY)/PixSizeY);
	if (value < 0)
		value = 0;
	return value;
}
/**********************************************
A ver si aqui no molesta
**********************************************/
/*boton_t botonera;

void inicializa(boton_t *b, int x0, int y0, int x1, int y1, int nx, int ny, int color ){
    int ancho = x1 - x0;
    int alto = y1 - y0;
    int i,j;
    int anchob = (ancho - (nx-1) * MARGEN)/nx;
    int altob = (alto - (ny-1) * MARGEN)/ny;
    b->id=1;
    b->nx = nx;
    b->ny = ny;
    boton *B;
    b->botones = (boton *)calloc(nx*ny, sizeof(boton));
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            B = &b->botones[ny*i+j];
            B->id = ny*i+j;
            B->color = color;
            B->x0 = x0 + (i+0.5)*MARGEN + i*anchob;
            B->y0 = y0 + (j+0.5)*MARGEN + j*altob;
            B->x1 = B->x0 + anchob;
            B->y1 = B->y0 + altob;
        }
    }
}

void dibuja(boton_t *b){
    int i,j;
    int x,y;
    boton *B;
    for (i = 0; i < b->nx; i++){
            for (j = 0; j < b->ny; j++){
                B = &b->botones[b->ny*i+j];
                SetXY(B->x0, B->x1, B->y0, B->y1);
                for (x=0; x< (B->y1 - B->y0) * (B->x1 - B->x0); x++)
                    Write_Data(B->color);
            }
        }
}
*/

/**********************************************
Arduino functions zone
**********************************************/
void setup()
{ 
  Lcd_Init();
  /*if (!card.init(SPI_HALF_SPEED, 10))
  {
    while(1)
    {
      Pant(0xffff);
      Pant(0x0000);
    }
  }
  */
  Touch_Init();
  LCD_clear();
	/*Pant(0xf800);
	Pant(0x07e0);
	Pant(0x001f);
	Pant(0xffff);
	Pant(0x0000);*/
  inicializa(&botonera,0,0,240,320,2,3,0x9999);
  dibuja(&botonera);
}

void loop()
{
    unsigned int  i,j;
   	while(Touch_DataAvailable() == 1)
	{
		Touch_Read();
		i = Touch_GetX();
		j = Touch_GetY();
		SetXY(i-1,i+1,j-1,j+1);
                for (int i=0;i<9;i++)
		Write_Data(0xaa*i%0xFFFF);
	}
}
/*
#ifdef __cplusplus
}
#endif*/
