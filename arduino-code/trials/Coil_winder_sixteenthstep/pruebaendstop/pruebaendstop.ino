// Ponemos nombre al motor, el número de pasos y los pins de control
//Stepper stepper(STEPS, 2, 5); //Stepper nombre motor (número de pasos por vuelta, pins de control)
int step_x = 2;
int dir_x = 5;
int enable = 8;
const int endstop_x = 9;
int value = 0;


void setup() {
  
  pinMode(enable, OUTPUT);
  pinMode(dir_x, OUTPUT);
  pinMode(step_x, OUTPUT);
  pinMode(endstop_x, INPUT);
  Serial.begin(9600);

  }

void loop() {

            for (int m = 1; m < 10000000; m++){
              
            value = digitalRead(endstop_x);
            
                if(value == LOW){
                  
                      Serial.println("Apagado");
                      digitalWrite(dir_x, HIGH);
                      delay(1); //Pequeña pausa
                      digitalWrite(step_x, HIGH);
                      delay(5); //Pequeña pausa
                      digitalWrite(step_x, LOW);
                      delay(5); //Pequeña pausa
             }
                 else{
                       digitalWrite(dir_x, LOW);
                       Serial.println("Encendido");

     }  
                            delay(100);
     }  
}   
