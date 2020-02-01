
const int inputPin = 9;
 
int value = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}
 
void loop(){
  value = digitalRead(inputPin);  //lectura digital de pin
 
  //mandar mensaje a puerto serie en función del valor leido
  if (value == HIGH) {
      Serial.println("Encendido");
  }
  else {
      Serial.println("Apagado");
  }
  delay(1000);
}
