/*
  LiquidCrystal Library - Custom Characters
 
 Demonstrates how to add custom characters on an LCD  display.  
 The LiquidCrystal library works with all LCD displays that are 
 compatible with the  Hitachi HD44780 driver. There are many of 
 them out there, and you can usually tell them by the 16-pin interface.
 
 This sketch prints "I <heart> Arduino!" and a little dancing man
 to the LCD.

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// make some custom characters:
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};
void setup() {
  // create a new character
  lcd.createChar(0, heart);
  // create a new character
  lcd.createChar(1, smiley);
  // create a new character
  lcd.createChar(2, frownie);
  // create a new character
  lcd.createChar(3, armsDown);  
  // create a new character
  lcd.createChar(4, armsUp);  

  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the lcd.
  lcd.print("  I  "); 
  lcd.write((byte)0);
  lcd.print(" NY ");
  lcd.write((byte)1);
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  
  //while (!Serial);
}



  //722 - S  
  //480 - L  
  //307 - D  
  //131 - U  
  //002 - R

#define masomenos(x,v) (x > (v - 10) && x < (v + 10))

String boton(int i){
 if (masomenos(i,720)) return "S";
 else
 if (masomenos(i,480)) return "L";
 else
 if (masomenos(i,307)) return "D";
 else
 if (masomenos(i,130)) return "U";
 else
 if (masomenos(i,5)) {
  Keyboard.begin();
  Keyboard.print("xxx");
  Keyboard.end();
  return "R";
 }  
 else
 return ":";
}

void loop() {
  // read the potentiometer on A0:
  int sensorReading = analogRead(A0);
  int readA1 = analogRead(A1);
  // map the result to 200 - 1000:
  int mappedA1 = map(readA1, 0, 1023, 200, 1000);
  int mappedA0 = map(sensorReading, 0, 1023, 200, 1000);
  // set the cursor to the bottom row, 8th position:
  //lcd.setCursor(8, 1);
  // draw the little man, arms down:
  //lcd.write(3);
  //delay(10);
  //lcd.setCursor(8, 1);
  // draw him arms up:
  //lcd.write(4);
  
  lcd.setCursor(4, 1);
  //lcd.print("         ");
  lcd.setCursor(4, 1);
  lcd.print(mappedA0);
  
  lcd.setCursor(10, 1);
  lcd.print(mappedA1);

  lcd.setCursor(2, 1);
  lcd.print(boton(sensorReading));    
  
  delay(10); 
}
    


