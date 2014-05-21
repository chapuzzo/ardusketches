/* Arduino long exposure bracketing                                                                         */
/* Parts of the LCD menu and interrupt timer are taken from the nokia demo application at nuelectronics.com */
/*                                                                                                          */
/* 2009 Joergen Geerds, V0.32 released as a creative commons open source license, please give/leave credit  */
/* download and more info at                                                                                */
/* http://newyorkpanorama.com/2009/01/21/long-exposure-night-hdr-photography-with-arduino/                  */

#include "Nokia_lcd.h"
#include <avr/pgmspace.h>

//keypad debounce parameter
#define DEBOUNCE_MAX 15
#define DEBOUNCE_ON  10
#define DEBOUNCE_OFF 3 

#define NUM_KEYS 5

// joystick number
#define UP_KEY 3
#define LEFT_KEY 0
#define CENTER_KEY 1
#define DOWN_KEY 2
#define RIGHT_KEY 4

// general wait time between bracket shots, here 500ms
#define BRACKETWAIT 500

#define SHUTTERPIN 4      // which pin is the shutter connected to?
#define RELEASE 7         // pushbutton pin

#define EVMIN 19          // min 1 second
#define EVMAX 45          // max 120 min

// exposure value table in 0.5 EV steps in milliseconds
unsigned long exptime[] = {1, 2, 3, 4, 6, 8, 11, 17, 22, 33, 50, 67, 100, 125, 167, 250, 333, 500, 666, 1000, 1500, 2600, 3300, 4600, 6600, 8600, 10500, 15500, 20500, 30500, 40500, 60500, 90500, 120500, 180500, 240500, 360500, 480500, 600500, 900500, 1200500, 1800500, 2400500, 3600500, 4800500, 7200500};
char* expstr[] = {"1/1000s", "1/500s", "1/350s", "1/250s", "1/180s", "1/125s", "1/90s", "1/60s", "1/45s", "1/30s", "1/20s", "1/15s", "1/10s", "1/8s", "1/6s", "1/4s", "1/3s", "1/2s", "0.7s", "1sec", "1.5sec", "2sec", "3sec", "4sec", "6sec", "8sec", "10sec", "15sec", "20sec", "30sec", "40sec", "1min", "1.5min", "2min", "3min", "4min", "6min", "8min", "10min", "15min", "20min", "30min", "40min", "60min", "80min", "120min"};


// default values for exposure bracketing
// next version will write defaults to the eeprom and read them on startup
byte b = 27;            // base exposure 15 sec, from exptime[]
byte w = 3;              // +- 3EV
byte n = 5;              // 5 brackets

byte i;                  // generic counter
char tempstring[2];      // generic string
char tempstring2[4];     // generic string

// adc preset value, represent top value,incl. noise & margin,that the adc reads, when a key is pressed
// set noise & margin = 30 (0.15V@5V)
int  adc_key_val[NUM_KEYS] ={30, 128, 260, 374, 515 };


// debounce counters
byte button_count[NUM_KEYS];
// button status - pressed/released
byte button_status[NUM_KEYS];
// button on flags for user program 
byte button_flag[NUM_KEYS];


#define MENU_X	10
#define MENU_Y	10

void main_MENU(void);
void select_bracketwidth(void);
void select_numberofshots(void);
void select_baseexposure(void);


Nokia_lcd lcd=Nokia_lcd();

void InitPort(){
  DDRB=0x2F;
}

void setup(void){
  

   // setup interrupt-driven keypad arrays  
   // reset button arrays
   for(i=0; i<NUM_KEYS; i++){
     button_count[i]=0;
     button_status[i]=0;
     button_flag[i]=0;
   }
  
  // Setup timer2 -- Prescaler/256
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
  TCCR2B = (1<<CS22)|(1<<CS21);      
  
  ASSR |=(0<<AS2);

   // Use normal mode  
   TCCR2A =0;    
     //Timer2 Overflow Interrupt Enable  
     TIMSK2 |= (0<<OCIE2A);
     TCNT2=0x6;  // counting starts from 6;  
   TIMSK2 = (1<<TOIE2);    
 
  SREG|=1<<SREG_I;
  
  InitPort();
  LCD_BACKLIGHT(1);
  lcd.cLCD_Init();
  pinMode(RELEASE, INPUT); 
  

   
}

void loop(void){
    button_flag[i]=0;          // reset button flag
    main_MENU();               // make main menu

    while(true){               // repeat forever
    for(i=0; i<NUM_KEYS; i++){             // wait for anything to happen
       if(digitalRead(RELEASE) == LOW){    // red button on pin RELEASE is pressed (goes LOW)
         bracket();
         }
       if(button_flag[i] !=0){
         button_flag[i]=0;     // reset button flag
	 switch(i){
	   case LEFT_KEY:
                select_numberofshots();
	   case RIGHT_KEY:
                select_baseexposure();
	   }
	 }
       }
    }
}

         


void main_MENU(void){

        lcd.cLCD_Box(0,0, 131,131, FILL, WHITE);         // clear screen
        lcd.cLCD_String("Ready...",     MENU_X, MENU_Y, BLUE, LIGHTBLUE);
        lcd.cLCD_String("Press button", MENU_X, MENU_Y+10, BLUE, LIGHTBLUE);

        lcd.cLCD_String("Base Exp:",    MENU_X, MENU_Y+25, BLACK, WHITE);
        lcd.cLCD_String(expstr[b],      MENU_X+20, MENU_Y+35, RED, WHITE);
        lcd.cLCD_String("Bracket:",     MENU_X, MENU_Y+50, BLACK, WHITE);
        lcd.cLCD_String("+-    EV",     MENU_X+20, MENU_Y+60, RED, WHITE);
        lcd.cLCD_String(itoa(w, tempstring, 10),  MENU_X+50, MENU_Y+60, RED, WHITE);
        lcd.cLCD_String("# of shots:",  MENU_X, MENU_Y+75, BLACK, WHITE);
        lcd.cLCD_String(itoa(n, tempstring, 10),        MENU_X+20, MENU_Y+85, RED, WHITE);
        
        
}

void select_bracketwidth(void){
    button_flag[i]=0;  // reset button flag

        lcd.cLCD_Box(0,0, 131,131, FILL, WHITE);         // clear screen
        lcd.cLCD_String("Select",       MENU_X, MENU_Y, BLUE, LIGHTBLUE);
        lcd.cLCD_String("Bracket:",  MENU_X, MENU_Y+10, BLUE, LIGHTBLUE);
        lcd.cLCD_String("+-    EV",     MENU_X+20, MENU_Y+25, RED, WHITE);
        lcd.cLCD_String(itoa(w, tempstring, 10),  MENU_X+50, MENU_Y+25, RED, WHITE);
        
        while(true){
        for(i=0; i<NUM_KEYS; i++){             // wait for anything to happen

         if(button_flag[i] !=0){
           button_flag[i]=0;  // reset button flag
	     switch(i){
	       case UP_KEY:
		if (w<10) w++;          //+-11 EV should be enough
                lcd.cLCD_String("+-    EV",     MENU_X+20, MENU_Y+25, RED, WHITE);
                lcd.cLCD_String(itoa(w, tempstring, 10),  MENU_X+50, MENU_Y+25, RED, WHITE);
                break;
	       case DOWN_KEY:
	        if (w>1) w--;
                lcd.cLCD_String("+-    EV",     MENU_X+20, MENU_Y+25, RED, WHITE);
                lcd.cLCD_String(itoa(w, tempstring, 10),  MENU_X+50, MENU_Y+25, RED, WHITE);
                break;
	       case LEFT_KEY:
                select_baseexposure();
	       case RIGHT_KEY:
                select_numberofshots();
               }
	  }
	}
    }
}

void select_baseexposure(void){
    button_flag[i]=0;  // reset button flag


        lcd.cLCD_Box(0,0, 131,131, FILL, WHITE);         // clear screen
        lcd.cLCD_String("Select",       MENU_X, MENU_Y, BLUE, LIGHTBLUE);
        lcd.cLCD_String("Base Exp:",  MENU_X, MENU_Y+10, BLUE, LIGHTBLUE);
        lcd.cLCD_String("        ", MENU_X+20, MENU_Y+25, RED, WHITE);
        lcd.cLCD_String(expstr[b], MENU_X+20, MENU_Y+25, RED, WHITE);

        while(true){
          for(i=0; i<NUM_KEYS; i++){             // wait for anything to happen
            if(button_flag[i] !=0){
              button_flag[i]=0;                  // reset button flag
	      switch(i){
	        case UP_KEY:
		  if (b<= EVMAX-2) b=b+2;
                  lcd.cLCD_String("        ", MENU_X+20, MENU_Y+25, RED, WHITE);
                  lcd.cLCD_String(expstr[b], MENU_X+20, MENU_Y+25, RED, WHITE);
                  break;
	        case DOWN_KEY:
		  if (b>=EVMIN+2) b=b-2;
                  lcd.cLCD_String("        ", MENU_X+20, MENU_Y+25, RED, WHITE);
                  lcd.cLCD_String(expstr[b], MENU_X+20, MENU_Y+25, RED, WHITE);
                  break;
	        case LEFT_KEY:
		  loop();
	        case RIGHT_KEY:
                  select_bracketwidth();
                }
             }
	   }
        }
}


void select_numberofshots(void){
    button_flag[i]=0;  // reset button flag

        lcd.cLCD_Box(0,0, 131,131, FILL, WHITE);         // clear screen
        lcd.cLCD_String("Select",       MENU_X, MENU_Y, BLUE, LIGHTBLUE);
        lcd.cLCD_String("# of shots:",  MENU_X, MENU_Y+10, BLUE, LIGHTBLUE);
        lcd.cLCD_String("        ", MENU_X+20, MENU_Y+25, RED, WHITE);
        lcd.cLCD_String(itoa(n, tempstring, 10), MENU_X+20, MENU_Y+25, RED, WHITE);

        while(true){        
        for(i=0; i<NUM_KEYS; i++){             // wait for anything to happen

         if(button_flag[i] !=0){
           button_flag[i]=0;  // reset button flag
	     switch(i){
	       case UP_KEY:
		if (n<= 11) n=n+2;
                lcd.cLCD_String("        ", MENU_X+20, MENU_Y+25, RED, WHITE);
                lcd.cLCD_String(itoa(n, tempstring, 10), MENU_X+20, MENU_Y+25, RED, WHITE);
                break;
	       case DOWN_KEY:
		if (n>=3) n=n-2;
                lcd.cLCD_String("        ", MENU_X+20, MENU_Y+25, RED, WHITE);
                lcd.cLCD_String(itoa(n, tempstring, 10), MENU_X+20, MENU_Y+25, RED, WHITE);
                break;
	       case LEFT_KEY:
                select_bracketwidth();
	       case RIGHT_KEY:
		loop();
            }
	  }
	}
    }
}
	
// start bracket shooting
void bracket(){
        int ev;
        
        lcd.cLCD_Box(0,0, 131,131, FILL, WHITE);      // clear screen
        lcd.cLCD_String("Exposing:", MENU_X, MENU_Y+35, BLACK, WHITE); 
        lcd.cLCD_String("      ", MENU_X+20, MENU_Y+45, RED, WHITE);   // clear
        lcd.cLCD_String(expstr[b], MENU_X+20, MENU_Y+45, RED, WHITE);  // print current exposure time, here the base EV
        fire(exptime[b]);
        delay(BRACKETWAIT);
        
        // Do the EV Bracket dance
        for (byte i=(n-1)/2; i>=1; i--){
          ev = b-((4*w*i)/(n-1));          // bracket dance on the short side
          if (ev>=EVMIN){                  // only exposures 1 sec and longer
            lcd.cLCD_String("      ", MENU_X+20, MENU_Y+45, RED, WHITE); // clear
            lcd.cLCD_String(expstr[ev], MENU_X+20, MENU_Y+45, RED, WHITE); // print current exposure time
            fire(exptime[ev]);
            delay(BRACKETWAIT);
          }
          ev = b+((4*w*i)/(n-1));          // bracket dance on the long side
          if (ev<=EVMAX){                  // only exposures 120min and shorter
            lcd.cLCD_String("      ", MENU_X+20, MENU_Y+45, RED, WHITE); // clear
            lcd.cLCD_String(expstr[ev], MENU_X+20, MENU_Y+45, RED, WHITE); // print current exposure time
            fire(exptime[ev]);
            delay(BRACKETWAIT);
          }
        } // end EV Bracket dance
        main_MENU();
}


// open shutter for t milliseconds
void fire(unsigned long t){
        unsigned long t0;
        pinMode(SHUTTERPIN, OUTPUT);        //outpin gives output
        t0 = millis();
        digitalWrite(SHUTTERPIN, HIGH);     //fire
        while (millis() < t0+t){}           //wait t millisec
        digitalWrite(SHUTTERPIN, LOW);      //end fire
}


// The followinging are interrupt-driven keypad reading 
//  which includes DEBOUNCE ON/OFF mechanism, and continuous pressing detection


// Convert ADC value to key number
char get_key(unsigned int input)
{
	char k;
    
	for (k = 0; k < NUM_KEYS; k++)
	{
		if (input < adc_key_val[k])
		{
           
    return k;
        }
	}
    
    if (k >= NUM_KEYS)
        k = -1;     // No valid key pressed
    
    return k;
}

void update_adc_key(){
  int adc_key_in;
  char key_in;
  byte i;
  
  adc_key_in = analogRead(0);
  key_in = get_key(adc_key_in);
  for(i=0; i<NUM_KEYS; i++)
  {
    if(key_in==i)  //one key is pressed 
    { 
      if(button_count[i]<DEBOUNCE_MAX)
      {
        button_count[i]++;
        if(button_count[i]>DEBOUNCE_ON)
        {
          if(button_status[i] == 0)
          {
            button_flag[i] = 1;
            button_status[i] = 1; //button debounced to 'pressed' status
          }
		  
        }
      }
	
    }
    else // no button pressed
    {
      if (button_count[i] >0)
      {  
		button_flag[i] = 0;	
		button_count[i]--;
        if(button_count[i]<DEBOUNCE_OFF){
          button_status[i]=0;   //button debounced to 'released' status
        }
      }
    }
    
  }
}

// Timer2 interrupt routine -
// 1/(160000000/256/(256-6)) = 4ms interval

ISR(TIMER2_OVF_vect) {  
  TCNT2  = 6;
  update_adc_key();
}

