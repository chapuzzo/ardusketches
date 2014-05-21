int sideA[6] = {10, 16, 14, 15, A0, A1, A2, A3};

void setup(){
  for (int i = 0; i < 7; i++){
    pinMode(sideA[i], OUTPUT);
    digitalWrite(sideA[i], HIGH);
  }
}

void loop(){
}
