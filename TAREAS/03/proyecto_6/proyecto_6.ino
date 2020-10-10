//******************************************************************************
// Controlador de Iluminación.
// Control por nivel de iluminación (día - noche) y sensado de presencia.
// Elaborado por equipo 01
//septiembre 2020
//------------------------------------------------------------------------------
const int RELAY = 12;           // LED

// Teclas asociadas
const int on_key = 3;
const int off_key = 2;
int counter = 0, manual = 0;

// Conexiones de los sensores
const int LDR = A5;
const int PIR = 4;
//-----[ AJUSTES GENERALES ]-----
void setup() {
  pinMode(RELAY, OUTPUT);     //declaramos como salida
  pinMode(on_key, INPUT);     //declaramos como entrada
  pinMode(off_key, INPUT);    //declaramos como entrada
  pinMode(PIR, INPUT);        //declaramos como entrada

  // Ajuste de "Pull up" para teclas de ajuste
  digitalWrite(on_key, HIGH);
  digitalWrite(off_key, HIGH);
  digitalWrite(PIR, HIGH);

  digitalWrite(RELAY, LOW);     // Apagado del LED
}
//-----[ LAZO PRINCIPAL ]-----
void loop() {
  // Enciende las luces si se detecta movimiento y la intensidad de iluminación es baja
  if (digitalRead(PIR) == HIGH) {
    counter = 1000;             // Ajusta el tiempo para 10 segundos
    if (counter > 15)           // Movimiento detectado por 1.5 segundos
    {
      if (analogRead(LDR) > 512) // La intensidad de la luz es baja
      {
        digitalWrite(RELAY, HIGH); // Enciende las iluminación
      }
    }
  }

  counter--;
  if (counter == 0) {
    if (manual == 0)            // Revisa esta opción.
    {
      digitalWrite(RELAY, LOW);
    }
  }

  // Obtención del punto de ajuste del usuario
  if (digitalRead(on_key) == LOW)
  {
    digitalWrite(RELAY, HIGH);  // Encendido de las luces
    manual = 1;                 // Encendido manual
  }
  if (digitalRead(off_key) == LOW)
  {
    digitalWrite(RELAY, LOW);   // Apagado de las luces
    manual = 0;
  }
  delay(10);                    // ACtualización cada 10 milisegundos
}
//******************************************************************************
