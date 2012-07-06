#include <SuperFastHash.h>

int dummy = 0;
char *input;
int i=0;
boolean hasheable= false;
int dummy2 = 0;

void setup(){
  dummy++;
  dummy2++;
  Serial.begin(9600);
  Serial.println(" -<");
  pinMode(13, OUTPUT);
  input = (char*)calloc(50,1);
  
}

void hashea(){
  Serial.println(input);
  Serial.println(SuperFastHash(input,strlen(input)),HEX);
  hasheable = false;
}

void loop(){
  digitalWrite(13,HIGH);
  //for (int i = 0; i < strlen(a); i++)
  char rd;
  while((rd = (char)Serial.read())){
    Serial.print(rd);
    hasheable = true;
    input[i++%50] = rd;     
    /*Serial.print(i);
    Serial.print(" ->");
    Serial.print( Serial.available());
    Serial.print(" ->");
    Serial.println(input[i-1]);*/
  }
  input[i%50] = 0;
  if (hasheable && strlen(input) > 0 && Serial.available() == 0 ) hashea();
  digitalWrite(13,LOW);
  i=0;
}
