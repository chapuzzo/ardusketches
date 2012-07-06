/*simonsays
by luismax
*/
int dummmy=999;
int timer = 100;
int inPins[] = {8,9,10,11};
int outPins[] = {5,6,7,4};
const int nleds = 4;

typedef struct lev {
  int length;
  int buttons[50];
} level;

level l;

void resetLevel(){
  l.length = 0;  
}

void createLevel(int cmp){
  while (cmp > l.length){
    l.buttons[l.length] = random(0,nleds);
    Serial.println(String("boton ")+l.length+String(":")+l.buttons[l.length]);
    l.length++;
  }
}

void displayLevel(){
  Serial.print(l.length);
  Serial.print(" : ");
  for (int i = 0; i< l.length; i++){
   digitalWrite(outPins[l.buttons[i]],LOW);
   Serial.print(l.buttons[i]);
   Serial.print(',');
   delay(timer*2);
   digitalWrite(outPins[l.buttons[i]],HIGH);
   delay(timer*2);
  }
  Serial.println(";");
  
}

int leeBoton(){
  while (1){
    for (int i = 0; i < nleds; i++)
    {
       if ( !digitalRead(inPins[i]))
       {
         Serial.println(String("pin ")+i+String(" pulsado"));
         while (!digitalRead(inPins[i]));
         Serial.println(String("pin ")+i+String(" soltado"));
         return i;
       }
    }
  }
}

bool tryLevel(){
  int ok = 0;
  for (int c = 0; c < l.length; c++){
    if (leeBoton() == l.buttons[c]){
      ok ++;
    }
    else {
      break;
    }
  }
  if (ok == l.length){
    Serial.println("nivel pasado"); 
    return true; 
  }
  Serial.println(ok);
  blink(8);
  Serial.println("volvemos a empezar");
  return false; 
}

void blink(int t){
  while (t--)
    {
      for (int i = 0; i < nleds; i++)
      {
          digitalWrite(outPins[i],LOW);
          delay(3);
          digitalWrite(outPins[i],HIGH);
      }
      delay(timer);
    }
}

void zigzag(){
  
      for (int i = 0; i < nleds; i++)
      {
          digitalWrite(outPins[i],LOW);
          delay(timer/2);
          digitalWrite(outPins[i],HIGH);
      }
      for (int i = nleds-i; i >= 0 ; i--)
      {
          digitalWrite(outPins[i],LOW);
          delay(timer/2);
          digitalWrite(outPins[i],HIGH);
      }
}

void setup() {
  dummmy++;
  Serial.begin(9600);
 for (int i = 0; i < nleds; i++)
  {
    pinMode(outPins[i],OUTPUT);
  }
 for (int i = 0; i < nleds; i++)
  {
    pinMode(inPins[i],INPUT);
  }
  
  blink(4);
  randomSeed(analogRead(A0));
  delay(500);
   
}

void loop(){
  
  for (int i = 1; i < 50; i++){
    createLevel(i);
    displayLevel();
    if (!tryLevel()) {
      resetLevel();
      break;
    }
    else {
      zigzag();
    }
    delay(1000);
  }
}
