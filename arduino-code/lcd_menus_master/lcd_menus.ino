#include <LiquidCrystal.h>    //Funciones del LCD
#include <Wire.h>
 
//Indica a la librería los pines de conexión del shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
const int numeroDeMenus=3;

char tituloMenu[numeroDeMenus][16] = {
  "Longitud bobina",
  "Numero de capas",               
  "Inicio bobinado"
  };
  
int n=0;

char tituloSubmenu[numeroDeMenus][16] = 
{
  "L = ",
  "N = ",
  "               "};
  
int variable[3] = {0, 0, 0};

int adc_key_val[5] ={
  50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;
boolean luzEncendida=true;
boolean cursorActivo=false;
unsigned long time;
int x=0;
int y=0;


void setup()
{
  Serial.begin(9600);
  Wire.begin();        // Conexión al Bus I2C

  
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(3,0); 
  lcd.print("Bobinadora");
  lcd.setCursor(3,1); 
  lcd.print("Automatica");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);              //Llevar el cursor al inicio fila 1
  lcd.print("Introduzca los siguientes parametros"); 
  for (int positionCounter = 0; positionCounter < 20; positionCounter++) {
   lcd.scrollDisplayLeft();
   delay(300);  //Scrolling speed
  }
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(tituloMenu[x]);
  lcd.setCursor(0,1); 
  lcd.print(String(tituloSubmenu[x]) + String(variable[x]));
}

void loop()
{
//  // Si han pasado mas de 10 segundos apagamos la luz
//  if (millis()-time > 10000) {
//    pinMode(10, OUTPUT);
//    digitalWrite(10, LOW);
//    luzEncendida=false;
//  }
//  // Si han pasado mas de 5 segundos apagamos el cursor
//  if (millis()-time > 5000) {
//    lcd.noBlink();
//    cursorActivo=false;
//  } 

  adc_key_in = analogRead(0);    // Leemos el valor de la pulsacion
  key = get_key(adc_key_in);    // Obtenemos el boton pulsado

  if (key != oldkey)   // if keypress is detected
  
    delay(50);  // Espera para evitar los rebotes de las pulsaciones
    adc_key_in = analogRead(0);    // Leemos el valor de la pulsacion
    key = get_key(adc_key_in);    // Obtenemos el boton pulsado
    if (key != oldkey)    
    {
      // TODO: falta la comprobacion de si se ha desbordado el tiempo
      time = millis();  
      if (!luzEncendida) {  // Al pulsar cualquier tecla encendemos la pantalla
        pinMode(10, INPUT);
        luzEncendida=true;
      } 
      else {  // si la pantalla esta encendida seguimos funcionando normalmente
        oldkey = key;
        if (key >=0){  // Si se ha pulsado cualquier tecla
          lcd.blink();  // Mostramos el cursor parpadeando
          cursorActivo=true;
        }
        if (key == 0){  // Se ha pulsado la tecla derecha
          x++;
          //variable[x]=0;        
          if (x>numeroDeMenus-1) {
            Serial.println("Comienza el bobinado");
            Serial.println("Enviando parámetros a Arduino slave..."); // Se envían los parámetros de longitud y número de capas seleccionados por el usuario a la placa Arduino slave
            Wire.beginTransmission(8);
            Serial.println("Longitud:");
            Serial.println(variable[1]);
            Serial.println("Número de capas:");
            Serial.println(variable[2]);
            
            Wire.write(variable[1]); // sends one byte // Longitud
            Wire.write(variable[2]); // sends one byte // Numero de capas 
            Wire.endTransmission(); // stop transmitting
            delay(500); 

            x=numeroDeMenus-1; 
            }; 
        }
        if (key == 1) {  // Se ha pulsado la tecla arriba
          variable[x]++;
        }
        if (key == 2) {  // Se ha pulsado la tecla abajo
          variable[x]--;
          if (variable[x]<0) variable[x]=0;
        }
        if (key == 3) {  // Se ha pulsado la tecla izquierda
          x--;
          if (x<0) x=0;
        }
        if (key == 4){  // Se ha pulsado la tecla de seleccion
        }
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(tituloMenu[x]);
        lcd.setCursor(0,1); 
        lcd.print(String(tituloSubmenu[x]) + String(variable[x]));
        Serial.println(x);

      }
    
  }
  delay(50);
}

// Convertimos el valor leido en analogico en un numero de boton pulsado
int get_key(unsigned int input)
{
  int k;

  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
      return k;
    }
  }

  if (k >= NUM_KEYS)k = -1;  // Error en la lectura
  return k;
}
