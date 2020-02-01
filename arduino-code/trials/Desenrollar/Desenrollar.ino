// Ponemos nombre al motor, el número de pasos y los pins de control
//Stepper stepper(STEPS, 2, 5); //Stepper nombre motor (número de pasos por vuelta, pins de control)
int step_x = 2;
int dir_x = 5;
int enable = 8;
int step_y = 3;
int dir_y = 6;

//Definimos las características del la bobina que queremos devanar:
float L = 40; //Longitud de la bobina a devanar, en mm
float d = 0.5; //Diámetro del hilo de cobre, en mm
int a = L/d;//Nº de vueltas que hay que girar por capa
int o = d/0.2;
int N = 6;


void setup() {
  
  pinMode(enable, OUTPUT);
  pinMode(dir_x, OUTPUT);
  pinMode(step_x, OUTPUT);
  pinMode(dir_y, OUTPUT);
  pinMode(step_y, OUTPUT);

  }

void loop() {



               //Desenrollar hilo
                for (int m = 1; m < 10000000; m++){
                    digitalWrite(dir_x, LOW);
                    delay(1); //Pequeña pausa
                    digitalWrite(step_x, HIGH);
                    delay(0.5); //Pequeña pausa
                    digitalWrite(step_x, LOW);
                    delay(0.5); //Pequeña pausa   
                } 
                
                
                }
