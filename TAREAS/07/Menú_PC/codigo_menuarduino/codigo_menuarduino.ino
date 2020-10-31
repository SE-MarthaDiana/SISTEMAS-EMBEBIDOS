// Download 'SimpleDHT' library from the library manager to run this
// code successfully.
#include <SimpleDHT.h>

// for DHT22, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 5;
int led=6;
int luz=0;
int aux=0;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
   pinMode(led,OUTPUT);
}

void loop() {
  // start working...
  
  // read without samples.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if (luz == 1) {          //Si el char o byte recibido es un fin de linea, activa la bandera
      digitalWrite(led,HIGH);
    }
    if (luz == 0) {          //Si el char o byte recibido es un fin de linea, activa la bandera
      digitalWrite(led,LOW);
    }
    if (luz == 2) {          //Si el char o byte recibido es un fin de linea, activa la bandera
         
      for(int x=0; x<5; x++){
      digitalWrite(led,HIGH);
      delay(100);
      digitalWrite(led,LOW);
      delay(100);
      aux++;
      if (aux=5){
        luz=0;
      }
      }
    }
  if ((err = dht11.read2(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
    return;
  }
  
  Serial.print((float)temperature);
  Serial.print(",");
  Serial.println((float)humidity);
  
  // DHT22 sampling rate is 0.5HZ.
  delay(2500);
  
}
  void serialEvent(){
  //Recepción de datos Seriales
  
  while (Serial.available()) {              //Si existen datos seriales, leer a todos
    byte CaracterEntrada = Serial.read();   //Leer 1 byte serial recibido
   
   // cadenaCharEntrada += CaracterEntrada;   //Agregar el nuevo char a una cadena String 
    if (CaracterEntrada == 65) {          //Si el char o byte recibido es un fin de linea, activa la bandera
      luz=1;
    }
    if (CaracterEntrada == 64) {          //Si el char o byte recibido es un fin de linea, activa la bandera
      luz=0;
    }
    if (CaracterEntrada == 63) {          //Si el char o byte recibido es un fin de linea, activa la bandera
      luz=2;
    }
    
  }
  
}
