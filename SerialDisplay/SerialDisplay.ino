/*
Mi primer Menu
*/

#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);
}

String s;
boolean printed = false;

void st_store(String s){
 EEPROM.write(0,s.length());
 for (int i=0; i < s.length(); i++)
  EEPROM.write(i+1,s[i]);
}

String st_read(){
 String res = "";
 int len = EEPROM.read(0);
 for (int i=0; i < len; i++)
  res += (char)EEPROM.read(i+1);
 return res;
}

void printIt(String s){
  lcd.setCursor(0,0);
  lcd.print(s.substring(0,16));
  if (s.length() > 16)
  {
    lcd.setCursor(0,1);
    lcd.print(s.substring(16,32));
  }
}  

void loop()
{
  if (Serial.available()) {
    s = "";
    //delay(100);
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
}
