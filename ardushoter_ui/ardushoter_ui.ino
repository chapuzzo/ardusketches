#include <menu.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

//#define DEBUG

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){  
  lcd.begin(16,2);
  pinMode(A3,OUTPUT);
 #ifdef DEBUG
  lcd.print("Connect to Begin");
  while (millis() < 3000){ // && !Serial){
    //lcd.setCursor(1,1);
    //lcd.print("      ");
    lcd.setCursor(6,1);
    lcd.print(3000 - millis());
    delay(100);
  };
  Serial.begin(9600);
 #endif
  creaMenus();
}

void loop(){
  waitButtonPress();
  buttonDispatch();
}

void sensor(void){
  
}

void remote(void){
  
}

//String s;
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
