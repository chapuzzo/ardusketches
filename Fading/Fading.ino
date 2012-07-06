/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */

char dummyvariablecuzmaintainerborkethecompiler = 123;
int ledPins[]={8,9,10,11,12,13};
int pins = sizeof(ledPins);
String s;

void setup()  { 
  dummyvariablecuzmaintainerborkethecompiler++;  
  digitalWrite(13, LOW);
  s=String();
  Serial.begin(9600);
} 

void loop()  { 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    for (int i=0; i<pins; i++){
      analogWrite(ledPins[i], fadeValue);         
      s = String();
      s += "i:";
      s += i;
      s += " fadevalue:" ;
      s += fadeValue ;
      s += "pin: ";
      s += ledPins[i];
      Serial.println(s);
    }
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    for (int i=0; i<pins; i++)
      analogWrite(ledPins[i], fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}


