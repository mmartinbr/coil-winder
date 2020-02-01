#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
 
void setup() {
 //Definir las dimensiones del LCD (16x2)
 lcd.begin(16,2);
lcd.print("Hola osito"); // Enviar el mensaje
   }

   void loop() 
   {
       lcd.setCursor(0, 0);  // set the cursor to column 0, line 1
       lcd.print(millis() / 1000);  // print the number of seconds since reset:
   }
