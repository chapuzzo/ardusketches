//#include <EEPROM.h>
#include <LiquidCrystal.h>
#include "MiPrimerMenu.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
menu *root, *m;

void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);
  creaMenus();
}

void p_it(){
  //Keyboard.begin();
  const char *it="@#1234abcde";
  Keyboard.write("@#1234abcde");
  //Keyboard.end();
  lcd.setCursor(9,1);
  lcd.print(it);
}

void creaMenus(){
  root = (menu*)calloc(10,sizeof(menu));
  //              texto            , abbr, ini ,  s  ,    l  ,    u  ,    d  ,   r
  root[0] = (menu){"Menu Principal", 'P', NULL, p_it, root+1, root+2, root+3, root+4 };
  root[1] = (menu){"Izquierda     ", 'L', NULL, NULL, root+1, root+2, root+3, root+4 };
  root[2] = (menu){"Arriba        ", 'U', NULL, NULL, root+1, root+2, root+3, root+4 };
  root[3] = (menu){"Abajo         ", 'D', NULL, NULL, root+1, root+2, root+3, root+4 };
  root[4] = (menu){"Derecha       ", 'R', NULL, NULL, root+1, root+2, root+3, root+4 };  
  setMenu(root);
}

void setMenu(menu *m_){
  if (m_ != NULL) 
    m = m_;
  printIt(m->texto);
  if (m->i){
    m->i();
  }
  Serial.println(m->abbr);
  lcd.setCursor(1,1);
  lcd.print(millis());
}

#define UMBRAL 10
#define masomenos(x,v) (x > (v - UMBRAL) && x < (v + UMBRAL))

char boton(int i){
  if (masomenos(i,720))
    return 'S';
  if (masomenos(i,480))
    return 'L';
  if (masomenos(i,307))
    return 'D';  
  if (masomenos(i,130))
    return 'U';
  if (masomenos(i,5))
    return 'R';
  return 'X';
}

void loop(){
  int a0;
  while ((a0 = analogRead(A0)) == 1023);
  switch (boton(a0)){
    case 'L': setMenu(m->l); while(boton(analogRead(A0))=='L'); break;
    case 'R': setMenu(m->r); while(boton(analogRead(A0))=='R'); break;
    case 'U': setMenu(m->u); while(boton(analogRead(A0))=='U'); break;
    case 'D': setMenu(m->d); while(boton(analogRead(A0))=='D'); break;
    case 'S': if (m->s != NULL)m->s(); while(boton(analogRead(A0))=='S'); break;
  }
  //delay(10);
}

String s;
/*
boolean printed = false;

void st_store(String s){
  EEPROM.write(0, s.length());
  for (int i=0; i < s.length(); i++)
    EEPROM.write(i+1, s[i]);
}

String st_read(){
  String res = "";
  int len = EEPROM.read(0);
  for (int i=0; i < len; i++)
    res += (char)EEPROM.read(i+1);
  return res;
}
*/
void printIt(String s){
  lcd.setCursor(0,0);
  lcd.print(s.substring(0,16));
  if (s.length() > 16)
  {
    lcd.setCursor(0,1);
    lcd.print(s.substring(16,32));
  }
} 
/*
void st_rd_test()
{
  if (Serial.available()) {
    s = "";
    delay(500);
    lcd.clear();
    while (Serial.available() > 0) {
      s += (char)Serial.read();
    }
    st_store(s);
    printIt(s);
  }
  else if (!printed){
    s = st_read();
    printIt(s);
    printed = true;
  }
}*/
