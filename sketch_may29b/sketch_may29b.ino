 
const int trigger=5;
const int echo=6;
 
float distance;
 
void setup(){
  while(!Serial);
  Serial.begin(9600);
  
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(7,LOW);
  digitalWrite(4,HIGH);
  
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
}
 
void loop(){
//Inicializamos el sensor
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);
// Comenzamos las mediciones
// Enviamos una señal activando la salida trigger durante 10 microsegundos
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
// Adquirimos los datos y convertimos la medida a metros
 distance=pulseIn(echo,HIGH); // Medimos el ancho del pulso
                              // (Cuando la lectura del pin sea HIGH medira
                              // el tiempo que transcurre hasta que sea LOW
 distance=distance*0.0001657;
// Enviamos los datos medidos a traves del puerto serie y al display LCD
  Serial.println(distance);
  
}
