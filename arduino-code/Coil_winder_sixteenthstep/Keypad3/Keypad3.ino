#include <Keypad.h>; // Con esta linea llamamos a la librería Keypad para que arduino reconozca el teclado
char contrasena[]="2222"; // En esta linea creamos la constante de cadena llamada contraseña (el numero 2222 puede ser cambiado)
char codigo[4]; // Creamos otra constante, en esta se guardaran los caracteres que presionemos en nuestro teclado matricial 4x4
int cont=0; // Esta es una variable que nos servirá más adelante
  
const byte ROWS = 4; //Este código se estable para definir que nuestro teclado tiene 4 filas 
const byte COLS = 4; //Este código se estable para definir que nuestro teclado tiene 4 columnas
  
char hexaKeys[ROWS][COLS] = //En el siguiente matriz se agregan en orden las teclas que posee nuestro teclado
{
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
  
byte rowPins[ROWS] = {9, 8, 7, 6}; // Estos son los pines de conexión de Arduino de las columnas
byte colPins[COLS] = {5, 4, 3, 2}; //Estos son los pines de conexión de Arduino de las filas
  
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //En este punto el teclado se inicia y realiza el mapeo de sus teclas con respecto a la matriz colocada arriba
  
void setup()
{
 pinMode(13, OUTPUT); //El pin 13 sera nuestra salida digital (así aprovecharemos el led que pose)
 Serial.begin(9600); //Se inicia el puerto serial
}
  
void loop()
{
 char customKey = customKeypad.getKey(); //esta linea indica que el carácter presionado se guardara en la variable customKey
 if (customKey != NO_KEY) //Con este siclo preguntamos si se presiono una tecla, si se presiono entonce el ciclo continua
 {
 codigo[cont]=customKey; //se guardaran los caracteres presionados en codigo[cont]
 Serial.print(codigo[cont]); //Se imprime en nuestro monitor serial lo que este guardado en codigo[cont]
 cont=cont+1; //incrementamos la variable cont (esto con el fin de tener los 4 dígitos que requerimos)
 if(cont==4) //Ahora comienza otro siclo if, en el cual se pregunta si ya hay 4 datos guardados y si es así entonce el siclo continua
  
 {
  
 if(codigo[0]==contrasena[0]&&codigo[1]==contrasena[1]&&codigo[2]==contrasena[2]&&codigo[3]==contrasena[3])
 {
  
 digitalWrite(13,!digitalRead(13)); //si lo anterior es verdad entonces se encenderá el led, si se ingresa nuevamente la contraseña entonces se apagara
 Serial.println("Password correcta"); //si la contraseña es correcta entonces se imprime ""Password correcta")
  
 }
 if(codigo!=contrasena) //empieza un nuevo ciclo, esta vez indicamos si el código es diferente que la contraseña siga con el siclo
 {
  
 Serial.println("Password incorrecta"); // se imprime que que la Password es incorrecta
 }
  
 cont=0; //resetear a 0 la variable cont
 }
 }
}
