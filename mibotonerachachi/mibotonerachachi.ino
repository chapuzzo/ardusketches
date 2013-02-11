#include "digitalWriteFast.h"
#include "sha1.h"

// web: http://www.henningkarlsen.com/electronics

#include "UTFT.h"
#include "ITDB02_Touch.h"

#include <botonera.h>
extern botonera Bo1;
extern botonera Bo2;
// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Uncomment the next two lines for the ITDB02 Shield
UTFT        myGLCD(ITDB28,A5,A4,A3,A2);
ITDB02_Touch  myTouch(A1,A3,A0,8,9);

int x, y;
/*
char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";
*/
void setup()
{
  // Initial setup
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);

  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(0, 0, 255);
  
  inicializa(&Bo1,0,32,240,240,7,6,0x001f);
  dibuja_botonera(&Bo1);
  
  inicializa(&Bo2,240,200,320,240,2,1,0xf800);
  Bo2.botones[1].color = 0x07e0;
  bind(&Bo2.botones[1],sha1test);
  bind(&Bo2.botones[0],limpia);
  dibuja_botonera(&Bo2);

}

void parseanddo(botonera  *B,int x, int y){
      boton *b;
      b = parse_b(B,x,y);
      if (b != NULL)
      {
        myGLCD.print("   ",250,32);
        myGLCD.printNumI(b->id,250,32);
        myGLCD.setColor(0, 0, 255);
        pulsa_boton(b);
          while (parse_b(B,x,y) == b){
            myTouch.read();
            x=myTouch.getX();
            y=myTouch.getY();
          }
        if (b->funcion != NULL){
          (*b->funcion) ();
        }
        suelta_boton(b);
        } 
}

void loop()
{
  int res;
  
   while (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      myGLCD.setColor(255, 0, 0);
      myGLCD.drawPixel(x,y);
      myGLCD.setColor(255, 255, 255);
      parseanddo(&Bo1,x,y);      
      parseanddo(&Bo2,x,y);
    }
}

int sha1test(){
  redibujaB2();
  char res[100];
  int t0 = millis();
  valor(&Bo1,res);
  myGLCD.print(res,0,16,0);
  Sha1.init();
  Sha1.print(res);
  Keyboard.begin();
  printHash(Sha1.result());
  Keyboard.end();
  t0 = millis() - t0;
  myGLCD.printNumI(t0, 250, 60, 6);
}

void printPass(uint8_t *hash) {
  int i;
  char *all = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
  char res[41];
  for (i=0; i<20; i++) {
    res[i] = all[hash[i]%94];
    Keyboard.write(res[i]);   
  }
  res[20] = 0;
  myGLCD.print(res,0,0,0);
  Keyboard.println("");
}

void printHash(uint8_t *hash) {
  int i;
  char res[41];
  for (i=0; i<20; i++) {
    res[2*i] = "0123456789abcdef"[hash[i]>>4];
    res [2*i+1] = "0123456789abcdef"[hash[i]&0xf];
  }
  res[40] = 0;
  myGLCD.print(res,0,0,0);
  Keyboard.println(res);
}
/*
int aestest(){
  
  aes256_context ctxt; 
  
  uint8_t key[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  };
  
  aes256_init(&ctxt, key);
    
  uint8_t data[] = {
    0x61, 0x73, 0x64, 0x66, 0x61, 0x73, 0x64, 0x66,
    0x61, 0x73, 0x64, 0x66, 0x61, 0x73, 0x64, 0x66
  };
    
  aes256_encrypt_ecb(&ctxt, data);
    
  aes256_done(&ctxt);
  char *res=(char*)malloc(5), prt[33];
  int i;
  //for (i=0; i<16; i++)
  //{
    sprintf(res,"%X%X%X%X%X%X%X%X",data);
    
   // prt[2*i] = res[0];
    //prt[2*i+1] = res[1];
  //}
  //prt[2*i] = 0;
  myGLCD.print(res, 0,0,0);
  sprintf(res,"%X%X%X%X%X%X%X%X",&data[8]);
  myGLCD.print(res, 0,30,0);
  return 0;
}*/

