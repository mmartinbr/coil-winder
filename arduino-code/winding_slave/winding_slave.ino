#include <Wire.h>

int enable = 8;

//Inicializamos las variables de las características del la bobina que queremos devanar:
int L = 0; // Longitud de la bobina a devanar, en mm
int N = 0; //Número de capas



/*** MOTOR X (Slider) ***/
int step_x = 2;
int dir_x = 5;
boolean sentidox = LOW;
//int tx = 10;
int tx = 0.5;


//int pasosx = 1200; // Pasos a dar longitudinalmente para completar una capa: Este cálculo se hará en función de las variables introducidas por el usuario
//int pasosx = 0;
int pasosx = (16 * L / 0.2) - 2250; // - 10 es un ajuste

/*** MOTOR Y (Winder) ***/
int step_y = 3;
int dir_y = 6;
boolean sentidoy = LOW;
//int ty = 10; 
//int ty = 2;
int ty = 1.5; // 1 a lo mejor es rápido, cambiar por dos

int pasosy = 9600; //9600 Regulación de frecuencia movimiento Winder/Slider: Avanza en el eje x cada 3 vueltas
//int pasosy = 10;

// Final de carrera (Motor x)
int endstop_x = 9;
int value = 0; //Inicializamos la variable que almacena el valor leído en el final de carrera
int pasos_totales = pasosx*N;

int s = 0;
int i = 0; // Contador de capas
int porcentaje = 0;



void setup() {
 //Wire.begin(8);                

  Serial.begin(9600);
  pinMode(enable, OUTPUT);
  pinMode(dir_x, OUTPUT);
  pinMode(step_x, OUTPUT);
  pinMode(dir_y, OUTPUT);
  pinMode(step_y, OUTPUT);
  pinMode(endstop_x, INPUT_PULLUP);
  //Serial.print(pasosx);
  Serial.println("PASOS TOTALES");
  Serial.println(pasos_totales);

Serial.println(digitalRead(endstop_x));
// Posicionamiento inicial
  while (digitalRead(endstop_x) == LOW) {  // Avanzar hasta tocar el final de carrera
    digitalWrite(dir_x, HIGH);      
    digitalWrite(step_x, HIGH);
    delay(1);                      
    digitalWrite(step_x, LOW);
    delay(1);   
  }
  for (int m = 1; m < 150; m++) { // Retroceso hasta la posición inicial de bobinado
    digitalWrite(dir_x, LOW);     
    digitalWrite(step_x, HIGH);
    delay(2);                       
    digitalWrite(step_x, LOW);
    delay(2);   
  }
 Wire.begin(8); 
  Wire.onReceive(receiveEvent);

}




void loop() {
 //stepper (pasosx, pasosy);  //Función de movimiento de los motores
  //Wire.onReceive(receiveEvent);
 }




void stepper (int pasosx, int pasosy){
 digitalWrite (dir_x, sentidox);
 digitalWrite (dir_y, sentidoy);
 
 
//while (i < N) {
for (int i = 0; i <= N; i++) {
     for (int m = 1; m < pasosx; m++) {
         for (int s = 1; s < 64; s++) {
           digitalWrite (dir_x, sentidox);
           delay(1);
           digitalWrite(step_x, HIGH);
           delay(tx);
           digitalWrite(step_x, LOW);
           delay(tx);  
         }
         m = 64 + m;
         for (int k = 1; k < pasosy; k++) {
           value = digitalRead(endstop_x);
           if (value == LOW){
             digitalWrite(step_y, HIGH);
             delay(ty);
             digitalWrite(step_y, LOW);
             delay(ty);
           }
           else {
             sentidox = !sentidox;
             Serial.println("Fin de capa: ");
             Serial.println(i);
             delay(2000);
             break;
           }
          }
          
          Serial.println("Número de pasos en x:");
          Serial.println(m);
          porcentaje = ((m / pasos_totales)*100);
          Serial.println("% Bobinado:");
          Serial.println(porcentaje);
      }
      sentidox = !sentidox;
      Serial.println("Número de capas:");
      Serial.println(i);
      delay(2000);
      i = i + 1;
      //break;
      
  } 
 // Serial.println("FINAL DEL BOBINADO");       
 exit(0);
}


void receiveEvent(int howMany) { 
  while (1 < Wire.available()) { // loop through all but the last 
    int L = Wire.read(); // receive first byte as an integer (longitude)
    Serial.println(L); // print the integer  
    int N = Wire.read(); // receive second byte as an integer (number of layers)
    Serial.println(N); // print the integer
    pasosx = (16 * L / 0.2) - 2250; // - 10 es un ajuste
    stepper (pasosx, pasosy);  //Función de movimiento de los motores
  }

  }
