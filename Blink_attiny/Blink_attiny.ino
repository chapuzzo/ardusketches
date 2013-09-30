int led = 0;

void setup() {              
  pinMode(led, OUTPUT);     
}

void fade(int led, int min, int max, int time, int steps){
  double freq = (1.0 * time) / steps;
  double inc = (1.0 * (max - min)) / steps;
  for (double value = (double)min; abs((int)(value - (double)max)) > 0; value += inc){
   analogWrite(led, value);
   delay ((int)freq);
  }
}

void loop() {
    fade(led, 255, 32, 100, 10);
    fade(led, 32, 255, 100, 10);
    shiftOut
}
