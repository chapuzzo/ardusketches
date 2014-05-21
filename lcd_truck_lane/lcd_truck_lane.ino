/* Simple Car game for a 16x2 LCD display
	Originally by @TheRealDod, Nov 25, 2010

	Modified by @alesf, Dec 1, 2012
	For use with Arduino LCD Keyboard shield sold on DX.com.
	Code is cleaner and more readable.
	Removed potentiometer steering and added tact button controls (up, down).
	Added control for a new game (select button).

	The circuit:
	* LCD RS pin to digital pin 8
	* LCD Enable pin to digital pin 9
	* LCD D4 pin to digital pin 4
	* LCD D5 pin to digital pin 5
	* LCD D6 pin to digital pin 6
	* LCD D7 pin to digital pin 7
	* LCD R/W pin to ground
	* 10K resistor:
	* ends to +5V and ground
	* wiper to LCD VO pin (pin 3)

*/

#include <LiquidCrystal.h>

// Check pin settings before use.
// These pin settings are for LCD Keyboard shield sold on DX.com
// Wiring explained at http://www.arduino.cc/en/Tutorial/LiquidCrystal
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int INPUTPIN = A0; // Steering wheel analogue input
const int RANDOMPIN = 15; // an analog pin that isn't connected to anything

const int MAXSTEPDURATION = 300; // Start slowly, each step is 1 millisec shorter.
const int MINSTEPDURATION = 150; // This is as fast as it gets

const int NGLYPHS = 6;
// the glyphs will be defined starting from 1 (not 0),
// to enable lcd.print() of null-terminated strings
byte glyphs[NGLYPHS][8] = {
	// 1: car up
   {B00000,
	B01110,
	B11111,
	B01010,
	B00000,
	B00000,
	B00000,
	B00000}
	// 2: car down
  ,{B00000,
	B00000,
	B00000,
	B00000,
	B01110,
	B11111,
	B01010,
	B00000}
	// 3: truck up
  ,{B00000,
	B11110,
	B11111,
	B01010,
	B00000,
	B00000,
	B00000,
	B00000}
	// 4: truck down
  ,{B00000,
	B00000,
	B00000,
	B00000,
	B11110,
	B11111,
	B01010,
	B00000}
	// 5: crash up
  ,{B10101,
	B01110,
	B01110,
	B10101,
	B00000,
	B00000,
	B00000,
	B00000}
	// 6: crash down
  ,{B00000,
	B00000,
	B00000,
	B10101,
	B01110,
	B01110,
	B10101,
	B00000}
};

// Possible car positions
const int NCARPOSITIONS = 4;

// Each position is mapped to a column of 2 glyphs
// Used to make sense when I had a 5th position
// where car or crash was drawn as 2 glyphs
// (can't do that since 0 terminates strings),
// so it's kinda silly now, but it ain't broke :)
const char BLANK = 32;
char car2glyphs[NCARPOSITIONS][2] = {{1, BLANK},{2, BLANK},{BLANK, 1},{BLANK, 2}};
char truck2glyphs[NCARPOSITIONS][2] = {{3, BLANK},{4, BLANK},{BLANK, 3},{BLANK, 4}};
char crash2glyphs[NCARPOSITIONS][2] = {{5, BLANK},{6, BLANK},{BLANK, 5},{BLANK, 6}};

const int ROADLEN = 15; // LCD width (not counting our car)
int road[ROADLEN]; // positions of trucks
char line_buff[2 + ROADLEN]; // aux string for drawRoad()
int road_index;
int car_pos;
// Off-the-grid position means empty column, so MAXROADPOS
// determines the probability of a car in a column
// e.g. 3 * NCARPOSITIONS gives p = 1/3
const int MAXROADPOS = 3 * NCARPOSITIONS;
int step_duration;

int crash; // true if crashed
unsigned int crashtime; // millis() when crashed
unsigned long gamestart = 0;

const char *INTRO1="Trucks ahead,";
const char *INTRO2="drive carefully";
const int INTRODELAY = 2000;

void setup()
{

	randomSeed(analogRead(RANDOMPIN));	// randomly position a truck;
	for (int i = 0; i < NGLYPHS; i++) {
		lcd.createChar(i + 1, glyphs[i]);	// create glyphs
	}

	lcd.begin(16, 2);

	start();

}

void loop() {

	getSteeringWheel();

	if (!crash) {
		crash = (car_pos==road[road_index]);
	}

	if (crash) {
		if (!crashtime) {
			crashtime = millis()-gamestart;
			drawRoad();
			// Game over text
			// (keep first 2 "crash" columns intact)
			lcd.setCursor(2, 0);
			lcd.print("GAME OVER!");
			lcd.setCursor(2, 1);
			lcd.print(crashtime/1000);
			lcd.print(" seconds.");
		}

		delay(10); // Wait a bit between writes

	} else {

		int prev_pos = road[(road_index-1)%ROADLEN];
		int this_pos = random(MAXROADPOS);

		while (abs(this_pos-prev_pos)<2) { // don't jam the road
			this_pos = random(MAXROADPOS);
		}

		road[road_index] = this_pos;
		road_index = (road_index + 1) % ROADLEN;
		drawRoad();
		delay(step_duration);
		if (step_duration > MINSTEPDURATION) {
			step_duration--; // go faster
		}
	}

}

void start() {

	for (int i = 0; i < ROADLEN; i++) {
		road[i]=-1; // setup road
	}

	crash = crashtime = road_index = car_pos = 0;
	step_duration = MAXSTEPDURATION;
	line_buff[1 + ROADLEN] = '\0'; // null terminate it

	getSteeringWheel();
	drawRoad();

	lcd.setCursor(1, 0);
	lcd.print(INTRO1);
	lcd.setCursor(1, 1);
	lcd.print(INTRO2);
	delay(INTRODELAY);

	gamestart = millis();
}

void getSteeringWheel() {

	// read LCD Keyboard shield buttons
	int button = analogRead(INPUTPIN) >> 7; // this removes least significant bits to get more stable reads.
	switch(button) {
		case 0: break; // button right
		case 1: car_pos--; break; // button up
		case 2: car_pos++; break; // button down
		case 3: break; // button left
		case 5: if(crash) start(); break; // button select
		case 7: break; // no button
	}
	if(car_pos > NCARPOSITIONS) car_pos = NCARPOSITIONS;
	if(car_pos < 0) car_pos = 0;
}

void drawRoad() {

	for (int i = 0; i < 2; i++) {
		if (crash) {
			line_buff[0]=crash2glyphs[car_pos][i];
		} else {
			line_buff[0]=car2glyphs[car_pos][i];
		}

		for (int j = 0; j < ROADLEN; j++) {
			int pos = road[(j + road_index)%ROADLEN];
			line_buff[j + 1] = pos>=0 && pos < NCARPOSITIONS ? truck2glyphs[pos][i] : BLANK;
		}

		lcd.setCursor(0, i);
		lcd.print(line_buff);
	}
}