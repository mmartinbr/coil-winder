
int enable = 8;

//Definimos las características del la bobina que queremos devanar:
float L = 44; // Longitud de la bobina a devanar, en mm
int N = 3; //Número de capas



/*** MOTOR X (Slider) ***/
int step_x = 2;
int dir_x = 5;
boolean sentidox = LOW;
//int tx = 10;
int tx = 1;
int pasosx = (16 * L / 0.2) - 10; // - 10 es un ajuste
//int pasosx = 1200; // Pasos a dar longitudinalmente para completar una capa: Este cálculo se hará en función de las variables introducidas por el usuario

/*** MOTOR Y (Winder) ***/
int step_y = 3;
int dir_y = 6;
boolean sentidoy = LOW;
//int ty = 10; 
int ty = 2;
int pasosy = 9600; // Regulación de frecuencia movimiento Winder/Slider: Avanza en el eje x cada 3 vueltas
//int pasosy = 10;

// Final de carrera (Motor x)
int endstop_x = 9;
int value = 0; //Inicializamos la variable que almacena el valor leído en el final de carrera


int i = 0; // Contador de capas



void setup() {
  pinMode(enable, OUTPUT);
  pinMode(dir_x, OUTPUT);
  pinMode(step_x, OUTPUT);
  pinMode(dir_y, OUTPUT);
  pinMode(step_y, OUTPUT);
  pinMode(endstop_x, INPUT);
  Serial.begin(9600);
  Serial.print(pasosx);

  // Posicionamiento inicial
  while (digitalRead(endstop_x) == LOW) {  // Avanzar hasta tocar el final de carrera
    digitalWrite(dir_x, HIGH);      
    digitalWrite(step_x, HIGH);
    delay(2);                      
    digitalWrite(step_x, LOW);
    delay(2);   
  }
  for (int m = 1; m < 100; m++) { // Retroceso hasta la posición inicial de bobinado
    digitalWrite(dir_x, LOW);     
    digitalWrite(step_x, HIGH);
    delay(2);                       
    digitalWrite(step_x, LOW);
    delay(2);   
  }

}

void loop() {
 stepper (pasosx, pasosy);  //Función de movimiento de los motores
}



void stepper (int pasosx, int pasosy){
 digitalWrite (dir_x, sentidox);
 digitalWrite (dir_y, sentidoy);
while (i < N) {
     for (int m = 1; m < pasosx; m++) {
         digitalWrite (dir_x, sentidox);
         delay(1);
         digitalWrite(step_x, HIGH);
         delay(tx);
         digitalWrite(step_x, LOW);
         delay(tx);
         for (int k = 1; k < pasosy; k++) {
           value = digitalRead(endstop_x);
           if (value == LOW){
             //Serial.println("Bobinando...");
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
            // n = n + 1;
             break;
           }
          }
      }
      sentidox = !sentidox;
      Serial.println("Fin de capa: ");
      Serial.println(i);
      delay(2000);
      i = i + 1;
      break;
  } 
  Serial.println("FINAL DEL BOBINADO");       
}
