#include <LiquidCrystal.h>
 
//Declarar LCD y pines
//http://jorgesanz.es/conectar-pantalla-lcd-a-arduino-uno/
 
LiquidCrystal lcd(7,6,5,4,3,2);
 
void setup() {
 //Definir las dimensiones del LCD (16x2)
 lcd.begin(16,2);
 //Seleccionamos en que columna y en que linea empieza a mostrar el texto
 lcd.setCursor(0,0);
 //Mostramos el texto deseado
 lcd.print("Hola mundo");
 lcd.setCursor(0,1);
 //Mostramos el texto deseado
 lcd.print("jorgesanz.es");
}
 
void loop() {
 
}
