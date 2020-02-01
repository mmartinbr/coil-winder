#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
 
void setup() {
 //Definir las dimensiones del LCD (16x2)
lcd.begin(16,2);
lcd.print("Hola mundo"); // Enviar el mensaje
   }

void loop()
   {
       lcd.setCursor(6, 1);    // Ponte en la line 1, posicion 6
       String s = reloj() ;
       lcd.print(s) ;
   }
String reloj()
   {
       int n = millis() / 1000 ;       // Lo pasamos a segundos
       int segundos = n % 60  ;
       int minutos =  n / 60  ;

       String S = String(minutos) + ":" + String(segundos);
       return (S);
   }
