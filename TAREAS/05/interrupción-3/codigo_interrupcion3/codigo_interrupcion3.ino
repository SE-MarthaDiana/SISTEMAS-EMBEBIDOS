//******************************************************************************
// Ejemplo del uso de Atención a Interrupciones
//
// Interrupciones asociadas recepciones seriales
//
//******************************************************************************
// ---[ BIBLIOTECAS ]---
// De momento no se necesitan
volatile char incomingByte; //creamos la variable
void setup() {
  Serial.begin(57600);       //la velocidad en bauds

}

void loop() {

}
void serialEvent(){
  Serial.println("Recibi:");        //imprimimos un letrero
  char incomingByte= Serial.read(); //leemos el canal serial 
  Serial.println(incomingByte);     //mostramos la letra recibida por el canal serial
  
  }
