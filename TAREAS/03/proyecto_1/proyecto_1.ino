

//******************************************************************************
// Revisión de una aplicación para un Sistema de Cerradura de una Puerta
// Aplicación simple para ensayar características de la plataforma Arduino.
// Autor:   Equipo_1
// Fecha:   Septiembre 2020
//******************************************************************************
//******incluir las librerías necesarias******
#include <Keypad.h>                 //librería para usar el teclado matricial
#include <LiquidCrystal_I2C.h>      //librería para usar el LCD con un modulo de comunicación LCD
//---[Habilitación de la LCD]---
LiquidCrystal_I2C lcd(0x27,20,4);   //declaración de la direccion de la LCD y el tamaño, en este caso es de 20 * 4
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//---[Habilitación del TECLADO]---
const byte ROWS = 4;  // Cuatro hileras del teclado
const byte COLS = 4;  // Cuatro Columnas del teclado
// Definición de los símbolos del teclado (serigrafía)
char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};
// Conexiones a las terminales del teclado:
byte rowPins[ROWS] = {3, 2, 1, 0};    // Hileras
byte colPins[COLS] = {7, 6, 5, 4};  // Columnas
// Inicialización de la una instancia del Teclado
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//---[Habilitación de Otros Elementos]---
const int LED_RED = 10;   // LED Rojo (Red)
const int LED_GREEN = 11; // LED Verde (Green)
const int RELAY = 12;     // Buzzer
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//---[ VARIABLES ]---
char keycount = 0;        // Conteo de intentos
char code[4];             // Retención de teclas oprimidas
//---[AJUSTES]-------------------------------------------------------------------
void setup() {
  pinMode(LED_RED, OUTPUT);     //declaramos como salida
  pinMode(LED_GREEN, OUTPUT);   //declaramos como salida
  pinMode(RELAY, OUTPUT);       //declaramos como salida
  // Ajuste de las características de la LCD 
  lcd.init();             //inicializa la LCD
  lcd.backlight();        //enciende la luz del fondo
  lcd.print("Equipo 1");  // Impresión de un mensaje en la LCD
  lcd.setCursor(0, 1);    // Mover cursor a la segunda línea
  lcd.print("ingrese la");  // Impresión de un mensaje en la LCD
  lcd.setCursor(0, 2);    // Mover cursor a la tercera línea
  lcd.print("contrasena");  // Impresión de un mensaje en la LCD
  lcd.setCursor(0, 3);      // Mover cursor a la cuarta línea
  lcd.cursor();           // Encender el cursor
  digitalWrite(LED_GREEN, HIGH);  // Prendido
  digitalWrite(LED_RED, LOW);     // Apagado
  digitalWrite(RELAY, LOW);       // Apagado del relevador
}
//---[CICLO]--------------------------------------------------------------------
void loop() {
  char customKey = customKeypad.getKey();  //obtiene los cáracteres tecleados

  if (customKey && (keycount < 4) && (customKey != '=') && (customKey != 'C')) {    
    // lcd.print(customKey);    // Para imprimir tecla introducida
    lcd.print('*');             // Enmascaramiento de info, para protección
    code[keycount] = customKey;
    keycount++;
  }
  if (customKey == 'C') {   // Tecla "Cancel/Lock" presionada para limpiar LCD...
    Lock();                 // ...y cerrar la puerta
  }
  if (customKey == '=') {   // Revisar Password y abrir
    if ((code[0] == '1') && (code[1] == '2') && (code[2] == '3') && (code[3] == '4'))
      // Verificar el password, por omisión: “1234”
    {
      digitalWrite(LED_GREEN, LOW); // Apaga LED Verde
      digitalWrite(LED_RED, HIGH);  // Enciende LED Rojo
      digitalWrite(RELAY, HIGH);    // Suena el buzzer
      lcd.clear();                        //limpia la LCD
      lcd.setCursor(0, 0);                //mover el cursor a la primera línea
      lcd.print("contrasena correcta");   //imprime mensaje
      lcd.setCursor(0, 1);                //mover el cursor a la segunda línea
      lcd.print("puerta abierta");        //imprime mensaje
      lcd.setCursor(0, 2);                //mover el cursor a la tercera línea
      lcd.print("equipo 1");              //imprime mensaje
      lcd.setCursor(0, 3);                //mover el cursor a la cuarta línea
      lcd.print("martha juan e isai");    //imprime mensaje
      delay(4000);                  // Se mantiene abierta por 4 segundos
      Lock();                             //llama a la función Lock
    }
    else
    {
      lcd.clear();                    //limpia la LCD
      lcd.setCursor(0, 1);            //mover el cursor a la segunda línea
      lcd.print("contrasena Invalida");  // Muestra mensaje de error
      delay(1500);                    // Espera un momento
      Lock();                         //llama a la función Lock
    }
  }
}
//******************************************************************************
//-----[ SUBRUTINAS y FUNCIONES ]-----
//---[Cerradura de Puerta y ACtualización de mensaje en la LCD ]---
void Lock() {
  lcd.clear();                    //limpia la LCD
  lcd.setCursor(0, 1);            //mover el cursor a la segunda línea
  lcd.print("= CERRADA =");       //imprime mensaje
  delay(1500);                    // Espera un tiempo
  lcd.setCursor(0, 1);            //mover el cursor a la segunda línea
  lcd.print("                ");  // Limpieza del password
  lcd.setCursor(0, 1);            //mover el cursor a la segunda línea
  keycount = 0;                   // Reinicia número de intentos
  digitalWrite(LED_GREEN, HIGH);  // LED Verde
  digitalWrite(LED_RED, LOW);     // LED Rojo
  digitalWrite(RELAY, LOW);       // Suena el buzzer
  lcd.clear();            //limpia la LCD
  lcd.print("Equipo 1");  // Impresión de un mensaje en la LCD
  lcd.setCursor(0, 1);    // Mover cursor a la segunda línea
  lcd.print("ingrese la");  // Impresión de un mensaje en la LCD
  lcd.setCursor(0, 2);    //mover el cursor a la tercera línea
  lcd.print("contrasena");  // Impresión de un mensaje en la LCD
  lcd.setCursor(0, 3);    //mover el cursor a la cuarta línea
  lcd.cursor();           // Encender el cursor
}
//******************************************************************************
