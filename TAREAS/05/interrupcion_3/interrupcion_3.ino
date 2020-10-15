//******************************************************************************
// Ejemplo del uso de Atención a Interrupciones
//
// Interrupciones asociadas recepciones seriales
//
//******************************************************************************
// ---[ BIBLIOTECAS ]---
// De momento no se necesitan
String incomingByte; //creamos la variable
String on="encender";
String off="apagar";

void setup() {
  pinMode (13, OUTPUT);
  Serial.begin(57600);       //la velocidad en bauds
  incomingByte.reserve(200);
}

void loop() {
 if (incomingByte==on){
  digitalWrite(13, HIGH);
 }
 if (incomingByte==off){
  digitalWrite(13, LOW);
 }
}
void serialEvent(){
  Serial.println("Recibi:");        //imprimimos un letrero
  char incomingByte= Serial.read(); //leemos el canal serial 
  Serial.println(incomingByte);     //mostramos la letra recibida por el canal serial
  
  }
