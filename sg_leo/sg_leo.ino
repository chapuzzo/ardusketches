
#include "SMARTGPU.h"
#include "sg_leo.h"
#include "sha256.h"
#include "aes256.h"
#include <grid.h>
#include <pgen.h>

SMARTGPU lcd;

#define GRID_SIZE 80
#define GRID_RATIO 2/6

#define DEBUG

char alfabeto[] = " 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_{|}`";
int longitud = strlen(alfabeto);
grid_ *gd;

void setup() {
  Keyboard.begin(ES);
#ifdef DEBUG  
  Serial.begin(9600);
#endif
  startScreen();
  gd = new grid_(WIDTH/GRID_SIZE,HEIGHT/GRID_SIZE);
}

void loop(){
  dispatchInput();
  //dispatchSerial();
}
  


void startScreen(){
  lcd.start();
  lcd.baudChange(1000000);
  restartScreen();
} 

void restartScreen(){
  lcd.orientation(LANDSCAPEL);
  lcd.imageSD(0,0,(char*)"luisito");
#ifdef DEBUG
  drawHouse();
  rejilla(GRID_SIZE, GRID_SIZE);
  lcd.putLetter(200,180,RED,FONT3,FILL,'x');
  delay(50);
  lcd.putLetter(200,180,GREEN,FONT3,FILL,'x');
  delay(50);
  lcd.putLetter(200,180,BLUE,FONT3,FILL,'x');
#endif
}

void printPass(uint8_t* hash) {
  for (int i=0; i<32; i++) {
#ifdef DEBUG
    Serial.print(alfabeto[hash[i]%longitud]);
#endif
    Keyboard.print(alfabeto[hash[i]%longitud]);
  }
#ifdef DEBUG
  Serial.println();
#endif
  Keyboard.println();
  delay(500);
}

void dispatchInput(){
  uint8_t buff[5];
  //uint16_t rd=0;
  lcd.touchRaw(buff);
  if (buff[0] == 0x4E){
    //la mayoria del tiempo esta aqui: sin pulsaciones.
  }
  else if ((buff[0]<<8 | buff[1] ) < 0x0200){
    // inspiracion aja de las 2:40 de la madrugada!!
    touch.p.x=map(buff[0]<<8|buff[1],0,320,0,330);
    touch.p.y=buff[2]<<8|buff[3];

    // descartamos mediciones invalidas
    if (touch.p.x > WIDTH  || touch.p.x < 0) return;
    if (touch.p.y > HEIGHT || touch.p.y < 0) return;

    // procesamos input
    marca(touch.p);
  }
  else {  
    Keyboard.begin();
    if (!strcmp((char*)buff,"PCMO")){
      Keyboard.print(alfabeto);
    }
    if (!strcmp((char*)buff,"CAME")){
      restartScreen();
      delete gd;
      gd = new grid_(WIDTH/GRID_SIZE,HEIGHT/GRID_SIZE);
    }
    if (!strcmp((char*)buff,"BOOK")){
      Keyboard.print("BOOK");
    }
    if (!strcmp((char*)buff,"HOME")){
      Sha256.init();
      Sha256.print((char*)gd->res());
      printPass(Sha256.result());
      Serial.println((char*)gd->res());
    }
    if (!strcmp((char*)buff,"MESG")){
      Keyboard.print("MESG");
    }
    Keyboard.end();
    delay(1000);
  }
}

void marca(pos_ p){
#ifdef DEBUG 
  char ss[200];
#endif
  const uint8_t chunks= GRID_SIZE;
  const uint8_t radius= chunks*GRID_RATIO;

#ifdef DEBUG  
  sprintf(ss,"p.x=%3d, p.y=%3d ", p.x, p.y);
  Serial.println(ss);
  lcd.string(180,195,320,240,WHITE,FONT3,FILL,ss);
#endif  

  uint16_t newX,newY;
  uint8_t chunkX,chunkY;

  chunkX = p.x/chunks;
  chunkY = p.y/chunks;

#ifdef DEBUG 
  sprintf(ss,"  x=%3d,   y=%3d ", chunkX, chunkY);
  Serial.println(ss);
  lcd.string(180,210,320,240,GREEN,FONT3,FILL,ss);
#endif

  newX= constrain(chunkX*chunks+chunks/2,0,WIDTH-1);
  newY= constrain(chunkY*chunks+chunks/2,0,HEIGHT-1);

  //lcd.putPixel(p.x,p.y,random());
  lcd.drawCircle(p.x, p.y, 3, RED, FILL);
  if (isInCircle(p,chunks,radius)){
    lcd.drawCircle(newX, newY, radius, random(), UNFILL);
    lcd.drawCircle(newX, newY, radius-1, WHITE, UNFILL);
    lcd.drawCircle(newX, newY, radius-2, WHITE, UNFILL);
    gd->marcame(chunkX,chunkY);
  }
}

// (x-a)**2 + (y-b)**2 = r**2;
uint8_t isInCircle(pos_ p, uint8_t gridsize, uint8_t radius){
  uint8_t relX = p.x%gridsize,
  relY = p.y%gridsize,
  center = gridsize/2;
  if ((relX-center)*(relX-center) + (relY-center)*(relY-center) <= radius*radius)
    return 1;
  return 0;
}


/*
void dispatchSerial(){
 if (s.available()){
 switch (s.read()){
 case 'S':
 xsub+=1;
 break;
 case 's':
 xsub-=1;
 break;
 case 'D':
 xdiv+=1;      
 break;
 case 'd':
 xdiv-=1;
 break;
 case 'r':
 s.println("restarting screen");
 lcd.reset();
 delay(2000);
 s.println("screen should start now");
 startScreen();
 return;
 break;
 default:
 return;
 break;
 }
 char ss[200];
 sprintf(ss,"xsub: %04X, ysub: %04X xdiv: %04X, ydiv: %04X", xsub,ysub,xdiv,ydiv);
 s.println(ss);
 lcd.string(5,180,190,240,RED,FONT3,FILL,ss);
 s.println(lcd.calibrate(xsub,ysub,xdiv,ydiv),HEX);
 } 
 }*/


/*firma[w]=  discretizar(touch.p.x, WIDTH, fact);
 firma[w+1]=discretizar(touch.p.y, HEIGHT, fact);
 
 s.print("x: ");
 s.print(touch.p.x);
 s.print(" (mod): ");
 s.print(firma[w]);
 s.print(" y: ");
 s.print(touch.p.y);
 s.print(" (mod): ");
 s.println(firma[w+1]);
 
 w+=2;
 sprintf(res, "%4d", w);
 lcd.string(200,200,320,240,WHITE,FONT3,FILL,res);
 if (w > MAX) w= 0;*/


//else if (buff[0] != 0x4E){

// save drawn positions
/*lcd.SDFopenFile(CREATEALWAYS, "firma.txt");
 lcd.SDFopenFile(WRITEONLY, "firma.txt");
 lcd.SDFwriteFile((w*sizeof(uint16_t)/sizeof(char)),(char*)firma,&rd);
 lcd.SDFcloseFile();
 
 s.print("w is: ");
 s.print(w);
 s.print(" rd is: ");
 s.println(rd);
 
 // clear screen*/
//restartScreen();
/*    
 // reset array signature 
 w=0;*/
//} 
//else
// NONE
//return ;

//delay(10);



