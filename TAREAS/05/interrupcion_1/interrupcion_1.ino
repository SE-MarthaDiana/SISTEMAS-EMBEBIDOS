//******************************************************************************
// Ejemplo del uso de Atención a Interrupciones
//
// Interrupciones asociadas a entradas de señales digitales
//letrero en la terminal del canal serial asíncrono (Tx, Rx, a 57.600 bauds) que especifique cuando ocurre la interrupción.
//******************************************************************************
const byte interruptPin = 2;              //declaramos el pin2 como nuestro pin para interrupciones
//ajuste principal
void setup() {
  Serial.begin(57600);                    //declaramos la velocidad a 57600 bauds
  attachInterrupt(digitalPinToInterrupt(interruptPin), cambio, CHANGE);   //creamos la función de la interrupción cada que se detecte un cambio 
}

void loop() {
  
}
//interrupción que manda el mensaje por el canal serial
void cambio() {
  Serial.println("interrupcion detectada");   //imprimimos el mensaje por el puerto serial.
}
