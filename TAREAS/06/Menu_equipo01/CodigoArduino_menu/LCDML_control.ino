// =====================================================================
//
// CONTROL v2.2.0
//
// =====================================================================
// *********************************************************************
// Caracteristicas
// - máximo. 6 botones con nombres especiales (entrar, salir, arriba, abajo, izquierda, derecha)
// Nuevas caracteristicas en v2.2.0
// - máximo 64 eventos, esto podría ser un botón o algo (Contador 0 - 63)
// - Los botones y eventos estándar se pueden utilizar al mismo tiempo.
// - El evento 0 - 3 se puede usar con una función de devolución de llamada de menú (cuando se configura este evento, se llama a la función)
// - El rango de 0 a 3 se puede cambiar en LCDMenuLib2.h
// Atención!!
// - los eventos deben reiniciarse manualmente sobre LCDML.CE_reset (number) o LCDML.CE_resetAll ();
// - no se reiniciarán desde la biblioteca de menús
// *********************************************************************
// Contenido:
// (0) Control sobre la interfaz serial con asdw_e_q
// (1) Control sobre una entrada analógica
// (2) Control sobre 4-6 pines de entrada digital (Pullups internas habilitadas)
// (3) Control sobre encoder [lib de terceros] (Descargar: https://github.com/PaulStoffregen/Encoder)
// (4) Control con Keypad  [lib de terceros] (Descargar: http://playground.arduino.cc/Main/KeypadTutorial )
// (5) Control con un control remoto IRMP [lib de terceros] (Descargar: https://github.com/ukw100/IRMP )
// (6) Control con un joystick
// (7) Control sobre I2C PCF8574
// *********************************************************************

#define _LCDML_CONTROL_cfg      2

// theory:
// "#if" es una directiva de preprocesador y no hay error, mira aquí:
// (English) https://en.wikipedia.org/wiki/C_preprocessor
// (German)  https://de.wikipedia.org/wiki/C-Pr%C3%A4prozessor

// *********************************************************************
// *************** (0) CONTROL SOBRE INTERFAZ SERIAL *******************
// *********************************************************************
#if(_LCDML_CONTROL_cfg == 0)
// CONFIGURACIONES
  # define _LCDML_CONTROL_serial_enter           'e'
  # define _LCDML_CONTROL_serial_up              'w'
  # define _LCDML_CONTROL_serial_down            's'
  # define _LCDML_CONTROL_serial_left            'a'
  # define _LCDML_CONTROL_serial_right           'd'
  # define _LCDML_CONTROL_serial_quit            'q'

  // ejemplo para el uso de eventos (no es necesario en todas partes)
  // esta definición es solo para ejemplos y se puede cambiar el nombre
  # define _LCDML_EVENT_command                'c'
  # define _LCDML_EVENT_char_0                 '0'
  # define _LCDML_EVENT_char_1                 '1'
  # define _LCDML_EVENT_char_2                 '2'
  # define _LCDML_EVENT_char_3                 '3'
  # define _LCDML_EVENT_char_4                 '4'
  # define _LCDML_EVENT_char_5                 '5'
  # define _LCDML_EVENT_char_6                 '6'
  # define _LCDML_EVENT_char_7                 '7'
  # define _LCDML_EVENT_char_8                 '8'
  # define _LCDML_EVENT_char_9                 '9'
// *********************************************************************

void lcdml_menu_control(void)
{
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup()) {
    // corre solo una vez 
  }

  if(LCDML.CE_setup()) {
    // corre solo una vez
    Serial.println("CE_setup()");
  }

  // compruebe si hay una nueva entrada en el puerto serie disponible
  if (Serial.available()) {
    // leer un carácter del búfer de entrada   
    switch (Serial.read())
    {
      case _LCDML_CONTROL_serial_enter:  LCDML.BT_enter(); break;
      case _LCDML_CONTROL_serial_up:     LCDML.BT_up();    break;
      case _LCDML_CONTROL_serial_down:   LCDML.BT_down();  break;
      case _LCDML_CONTROL_serial_left:   LCDML.BT_left();  break;
      case _LCDML_CONTROL_serial_right:  LCDML.BT_right(); break;
      case _LCDML_CONTROL_serial_quit:   LCDML.BT_quit();  break;
      // ejemplo de manejo de eventos
      // manejo de eventos personalizado
      // También es posible habilitar más de un evento al mismo tiempo
      // pero cuando más de un evento con funciones de devolución de llamada están activos
      // solo se llama a la primera función de devolución de llamada. (primero = por número)
      case _LCDML_EVENT_command:  LCDML.CE_set(0);   break;
      case _LCDML_EVENT_char_0:   LCDML.CE_set(1);   break;
      case _LCDML_EVENT_char_1:   LCDML.CE_set(2);   break;
      case _LCDML_EVENT_char_2:   LCDML.CE_set(3);   break;
      case _LCDML_EVENT_char_3:   LCDML.CE_set(4);   break;
      case _LCDML_EVENT_char_4:   LCDML.CE_set(5);   break;
      case _LCDML_EVENT_char_5:   LCDML.CE_set(6);   break;
      case _LCDML_EVENT_char_6:   LCDML.CE_set(7);   break;
      case _LCDML_EVENT_char_7:   LCDML.CE_set(8);   break;
      case _LCDML_EVENT_char_8:   LCDML.CE_set(9);   break;
      case _LCDML_EVENT_char_9:   LCDML.CE_set(10);  break;
      default: break;
    }
  }
}

// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************





// *********************************************************************
// *************** (1) CONTROL sobre una entrada analógica *********************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 1)

  unsigned long g_LCDML_DISP_press_time = 0;
// CONFIGURACIONES
  #define _LCDML_CONTROL_analog_pin              0
  // cuando no usó un botón, establezca el valor en cero
  #define _LCDML_CONTROL_analog_enter_min        850     // Button Enter
  #define _LCDML_CONTROL_analog_enter_max        920
  #define _LCDML_CONTROL_analog_up_min           520     // Button Up
  #define _LCDML_CONTROL_analog_up_max           590
  #define _LCDML_CONTROL_analog_down_min         700     // Button Down
  #define _LCDML_CONTROL_analog_down_max         770
  #define _LCDML_CONTROL_analog_back_min         950     // Button Back
  #define _LCDML_CONTROL_analog_back_max         1020
  #define _LCDML_CONTROL_analog_left_min         430     // Button Left
  #define _LCDML_CONTROL_analog_left_max         500
  #define _LCDML_CONTROL_analog_right_min        610     // Button Right
  #define _LCDML_CONTROL_analog_right_max        680
// *********************************************************************

void lcdml_menu_control(void)
{
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup()) {
    // corre solo una vez
  }
  // comprobar el temporizador antirrebote
  if((millis() - g_LCDML_DISP_press_time) >= 200) {
    g_LCDML_DISP_press_time = millis(); // reiniciar el temporizador antirrebote

    uint16_t value = analogRead(_LCDML_CONTROL_analog_pin);  // pin analógico para teclado

    if (value >= _LCDML_CONTROL_analog_enter_min && value <= _LCDML_CONTROL_analog_enter_max) { LCDML.BT_enter(); }
    if (value >= _LCDML_CONTROL_analog_up_min    && value <= _LCDML_CONTROL_analog_up_max)    { LCDML.BT_up();    }
    if (value >= _LCDML_CONTROL_analog_down_min  && value <= _LCDML_CONTROL_analog_down_max)  { LCDML.BT_down();  }
    if (value >= _LCDML_CONTROL_analog_left_min  && value <= _LCDML_CONTROL_analog_left_max)  { LCDML.BT_left();  }
    if (value >= _LCDML_CONTROL_analog_right_min && value <= _LCDML_CONTROL_analog_right_max) { LCDML.BT_right(); }
    if (value >= _LCDML_CONTROL_analog_back_min  && value <= _LCDML_CONTROL_analog_back_max)  { LCDML.BT_quit();  }
  }
}
// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************






// *********************************************************************
// *************** (2) CONTROL SOBRE PINES DIGITALES ***********************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 2)
// configuraciones
  unsigned long g_LCDML_DISP_press_time = 0;

  #define _LCDML_CONTROL_digital_low_active      0    // 0 = Alto activo (pulldown) botón, 1 = Bajo activo (pullup)
                                                      // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
  #define _LCDML_CONTROL_digital_enable_quit     1
  #define _LCDML_CONTROL_digital_enable_lr       1
  #define _LCDML_CONTROL_digital_enter           2
  #define _LCDML_CONTROL_digital_up              3
  #define _LCDML_CONTROL_digital_down            4
  #define _LCDML_CONTROL_digital_quit            5
  #define _LCDML_CONTROL_digital_left            12
  #define _LCDML_CONTROL_digital_right           13
// *********************************************************************
void lcdml_menu_control(void)
{
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup()) {
    // corre solo una vez
    // inicialización de botones
    pinMode(_LCDML_CONTROL_digital_enter      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_up         , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_down       , INPUT_PULLUP);
    # if(_LCDML_CONTROL_digital_enable_quit == 1)
      pinMode(_LCDML_CONTROL_digital_quit     , INPUT_PULLUP);
    # endif
    # if(_LCDML_CONTROL_digital_enable_lr == 1)
      pinMode(_LCDML_CONTROL_digital_left     , INPUT_PULLUP);
      pinMode(_LCDML_CONTROL_digital_right    , INPUT_PULLUP);
    # endif
  }

  #if(_LCDML_CONTROL_digital_low_active == 1)
  #  define _LCDML_CONTROL_digital_a !
  #else
  #  define _LCDML_CONTROL_digital_a
  #endif

  uint8_t but_stat = 0x00;

  bitWrite(but_stat, 0, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_enter)));
  bitWrite(but_stat, 1, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_up)));
  bitWrite(but_stat, 2, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_down)));
  #if(_LCDML_CONTROL_digital_enable_quit == 1)
  bitWrite(but_stat, 3, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_quit)));
  #endif
  #if(_LCDML_CONTROL_digital_enable_lr == 1)
  bitWrite(but_stat, 4, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_left)));
  bitWrite(but_stat, 5, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_right)));
  #endif

  if (but_stat > 0) {
    if((millis() - g_LCDML_DISP_press_time) >= 200) {
        g_LCDML_DISP_press_time = millis(); // restablecer el tiempo de presión

      if (bitRead(but_stat, 0)) { LCDML.BT_enter(); }
      if (bitRead(but_stat, 1)) { LCDML.BT_up();    }
      if (bitRead(but_stat, 2)) { LCDML.BT_down();  }
      if (bitRead(but_stat, 3)) { LCDML.BT_quit();  }
      if (bitRead(but_stat, 4)) { LCDML.BT_left();  }
      if (bitRead(but_stat, 5)) { LCDML.BT_right(); }
    }
  }
}
// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************






// *********************************************************************
// *************** (3) CONTROL CON ENCODER ****************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 3)
  /*
   * Thanks to "MuchMore" (Arduino forum) to add this encoder functionality
   *
   * rotate left = Up
   * rotate right = Down
   * push = Enter
   * push long = Quit
   * push + rotate left = Left
   * push + rotate right = Right
   */

  /* encoder connection
   * button * (do not use an external resistor, the internal pullup resistor is used)
   * .-------o  Arduino Pin
   * |
   * |
   * o  /
   *   /
   *  /
   * o
   * |
   * '-------o   GND
   *
   * encoder * (do not use an external resistor, the internal pullup resistors are used)
   *
   * .---------------o  Arduino Pin A
   * |        .------o  Arduino Pin B
   * |        |
   * o  /     o  /
   *   /        /
   *  /        /
   * o        o
   * |        |
   * '--------o----o   GND (common pin)
   */

  // DEFINCIONES GLOBALES
  #define encoder_A_pin       2    // El pin físico debe ser 2 o 3 para usar interrupciones (en mega, por ejemplo, 20 o 21), use pullups internos
  #define encoder_B_pin       3    // El pin físico debe ser 2 o 3 para usar interrupciones (en mega, por ejemplo, 20 o 21), use pullups internos
  #define encoder_button_pin  4    // pin físico, use pullup interno

  #define g_LCDML_CONTROL_button_long_press    800   // ms
  #define g_LCDML_CONTROL_button_short_press   120   // ms

  #define ENCODER_OPTIMIZE_INTERRUPTS //Solo cuando se usa pin2 / 3 (o 20/21 en mega)
  #include <Encoder.h> //para Encoder    Descargar:  https://github.com/PaulStoffregen/Encoder

  Encoder ENCODER(encoder_A_pin, encoder_B_pin);

  unsigned long  g_LCDML_CONTROL_button_press_time = millis();
  bool  g_LCDML_CONTROL_button_prev       = HIGH;

// *********************************************************************
void lcdml_menu_control(void)
// *********************************************************************
{
  // declarar variable para esta función
  int32_t g_LCDML_CONTROL_Encoder_position = ENCODER.read();
  bool g_LCDML_button                      = digitalRead(encoder_button_pin);
  
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup())
  {
    // corre solo una vez

    // pines de inicio, habilitar pullups
    pinMode(encoder_A_pin      , INPUT_PULLUP);
    pinMode(encoder_B_pin      , INPUT_PULLUP);
    pinMode(encoder_button_pin  , INPUT_PULLUP);
  }

  // comprobar si el codificador está girado en la dirección A
  if(g_LCDML_CONTROL_Encoder_position <= -3) 
  {
    // compruebe si el botón está presionado y el codificador está girado
    // el botón está bajo activo
    if(g_LCDML_button == LOW)
    {
      // botón presionado
      LCDML.BT_left();  

      //  Restablecer tiempo de pulsación del botón para la próxima detección
      g_LCDML_CONTROL_button_prev = HIGH;
    }
    else
    {
      LCDML.BT_down();
    }    

    // inicializar encoder para el siguiente paso
    ENCODER.write(g_LCDML_CONTROL_Encoder_position+4);
  }
  
  // comprobar si el codificador está girado en la dirección B
  else if(g_LCDML_CONTROL_Encoder_position >= 3)
  {    
    // compruebe si el botón está presionado y el codificador está girado
    // el botón está bajo 
    if(g_LCDML_button == LOW)
    {
      // botón presionado
      LCDML.BT_right(); 

      //  Restablecer tiempo de pulsación del botón para la próxima detección
      g_LCDML_CONTROL_button_prev = HIGH;
    }
    else
    {
      LCDML.BT_up();
    }   
    // inicializar encoder para el siguiente paso
    ENCODER.write(g_LCDML_CONTROL_Encoder_position-4);
  }
  else
  {
    // compruebe si el botón se presionó durante un tiempo breve o prolongado
    
    // borde descendente, botón presionado, sin acción
    if(g_LCDML_button == LOW && g_LCDML_CONTROL_button_prev == HIGH)  
    {
      g_LCDML_CONTROL_button_prev = LOW;
      g_LCDML_CONTROL_button_press_time = millis();
    }

    // flanco ascendente, botón no presionado, compruebe cuánto tiempo estuvo presionado   
    else if(g_LCDML_button == HIGH && g_LCDML_CONTROL_button_prev == LOW) 
    {
      g_LCDML_CONTROL_button_prev = HIGH;
      
      // comprobar cuánto tiempo estuvo pulsado el botón y detectar una pulsación larga o corta

      // comprobar situación de pulsación larga
      if((millis() - g_LCDML_CONTROL_button_press_time) >= g_LCDML_CONTROL_button_long_press)
      {
        // pulsación larga detectada
        LCDML.BT_quit();
      }
      // comprobar situación de pulsación corta
      else if((millis() - g_LCDML_CONTROL_button_press_time) >= g_LCDML_CONTROL_button_short_press)
      {
        // pulsación corta detectada
        LCDML.BT_enter();
      }
    }

    // hacer nada
    else 
    {
      // hacer nada
    }
  }
}
// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************





// *********************************************************************
// *************** (4) CONTROL CON TECLADO ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 4)
// librerias
  // más información http://playground.arduino.cc/Main/KeypadTutorial
  #include <Keypad.h>
// configuración
  #define _LCDML_CONTROL_keypad_rows 4 // 4 filas
  #define _LCDML_CONTROL_keypad_cols 3 // 3 columnas
// variables gllobales
  char keys[_LCDML_CONTROL_keypad_rows][_LCDML_CONTROL_keypad_cols] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'#','0','*'}
  };
  byte rowPins[_LCDML_CONTROL_keypad_rows] = { 9, 8, 7, 6 };  // conectar el teclado COL0, COL1 y COL2 en estps pines Arduino.
  byte colPins[_LCDML_CONTROL_keypad_cols] = { 12, 11, 10 };  // Crear el teclado
// objects
  Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, _LCDML_CONTROL_keypad_rows, _LCDML_CONTROL_keypad_cols );
// *********************************************************************
void lcdml_menu_control(void)
{
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup()) {
    // corre solo una vez
  }
  char key = kpd.getKey();
  if(key)  // Verifique una clave válida.
  {
    switch (key)
    {
      // Esta es la configuración por defecto
      case '#': LCDML.BT_enter(); break;
      case '2': LCDML.BT_up();    break;
      case '8': LCDML.BT_down();  break;
      case '4': LCDML.BT_left();  break;
      case '6': LCDML.BT_right(); break;
      case '*': LCDML.BT_quit();  break;

      // cuando quiera usar todos los caracteres, debe usar la  CE_ functionality
      // CE significa "evento personalizado" y puede definir 64 eventos
      // el siguiente código es solo un ejemplo      
      /*
      case '1': LCDML.CE_set(2); break;
      case '2': LCDML.CE_set(3); LCDML.BT_up();    break;
      case '3': LCDML.CE_set(4); break; 
      case '4': LCDML.CE_set(5); LCDML.BT_left();  break;
      case '5': LCDML.CE_set(6); break; 
      case '6': LCDML.CE_set(7); LCDML.BT_right(); break;
      case '7': LCDML.CE_set(8); break; 
      case '8': LCDML.CE_set(9); LCDML.BT_down();  break;
      case '9': LCDML.CE_set(10); break; 
      case '0': LCDML.CE_set(1); break; 
      case '#': LCDML.CE_set(12); LCDML.BT_enter(); break;
      case '*': LCDML.CE_set(11); LCDML.BT_quit();  break;
      */      
      default: break;
    }
  }
}
// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************


// *********************************************************************
// *************** (5) CONTROL CON IR REMOTO ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 5)
    // IR LIBRERIA (esta lib tiene que estar instalada)
    // Ruta de descarga: https://github.com/ukw100/IRMP
    #define IRMP_INPUT_PIN PA0
    #define IRMP_PROTOCOL_NAMES 1 //Habilite la asignación de números de protocolo a cadenas de protocolos; necesita algo de FLASH. Debe antes #include <irmp*>
    #include <irmpSelectMain15Protocols.h> // Esto habilita 15 protocolos principales

    #include <irmp.c.h>

    IRMP_DATA irmp_data[1];

    #define STR_HELPER(x) #x
    #define STR(x) STR_HELPER(x)

    void handleReceivedIRData();

// *********************************************************************
// cambie en esta función los valores de IR a sus valores
void lcdml_menu_control(void)
{
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup()) {
    // corre solo una vez
    irmp_init();
  }

  if (irmp_get_data(&irmp_data[0]))
  {
    // comenta esta línea para comprobar el código correcto
    //Serial.println(results.value, HEX);

    // en este caso de interruptor, debe cambiar el valor 0x ... 1 al código IR correcto
    switch (irmp_data[0].command)
    {
      case 0x52: LCDML.BT_enter(); break;
      case 0x50: LCDML.BT_up();    break;
      case 0x51: LCDML.BT_down();  break;
      case 0x55: LCDML.BT_left();  break;
      case 0x56: LCDML.BT_right(); break;
      case 0x23: LCDML.BT_quit();  break;
      default: break;
    }
  }
}
// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************



// *********************************************************************
// *************** (6) CONTROL CON JOYSTICK ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 6)
  unsigned long g_LCDML_DISP_press_time = 0;
    // Configuración
    #define _LCDML_CONTROL_analog_pinx A0
    #define _LCDML_CONTROL_analog_piny A1
    #define _LCDML_CONTROL_digitalread 33 //no trabaje con u8glib

    // cuando no usó un botón, establezca el valor en cero
    #define _LCDML_CONTROL_analog_up_min 612 // Botón arriba
    #define _LCDML_CONTROL_analog_up_max 1023
    #define _LCDML_CONTROL_analog_down_min 0 // Botón abajo
    #define _LCDML_CONTROL_analog_down_max 412
    #define _LCDML_CONTROL_analog_left_min 612 // Botón izquierda
    #define _LCDML_CONTROL_analog_left_max 1023
    #define _LCDML_CONTROL_analog_right_min 0 // Botón derecha
    #define _LCDML_CONTROL_analog_right_max 412
// *********************************************************************
void lcdml_menu_control(void)
{
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup()) {
    // corre solo una vez
    pinMode (_LCDML_CONTROL_digitalread, INPUT);
  }
  // comprobar el temporizador antirrebote
  if((millis() - g_LCDML_DISP_press_time) >= 200) {
    g_LCDML_DISP_press_time = millis(); // reinicia timer

    uint16_t valuex = analogRead(_LCDML_CONTROL_analog_pinx);  // analogpinx
    uint16_t valuey = analogRead(_LCDML_CONTROL_analog_piny);  // analogpinx
    uint16_t valuee = digitalRead(_LCDML_CONTROL_digitalread);  //digitalpinenter


    if (valuey >= _LCDML_CONTROL_analog_up_min && valuey <= _LCDML_CONTROL_analog_up_max) { LCDML.BT_up(); }        // arriba
    if (valuey >= _LCDML_CONTROL_analog_down_min && valuey <= _LCDML_CONTROL_analog_down_max) { LCDML.BT_down(); }    // abajo
    if (valuex >= _LCDML_CONTROL_analog_left_min && valuex <= _LCDML_CONTROL_analog_left_max) { LCDML.BT_left(); }     // izquierda
    if (valuex >= _LCDML_CONTROL_analog_right_min && valuex <= _LCDML_CONTROL_analog_right_max) { LCDML.BT_right(); }    // derecha

    if(valuee == true) {LCDML.BT_enter();}    // enter

    // los botones de retroceso deben incluirse como elemento del menú
    // mira el ejemplo LCDML_back_button
  }
}
// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************

// *********************************************************************
// *************** (7) CONTROL SOBRE PCF8574 ****************************
// *********************************************************************

#elif(_LCDML_CONTROL_cfg == 7)
  unsigned long g_LCDML_DISP_press_time = 0;
  #define PCF8574_1 0x26 // I2C DIRECCION PARA LOS BOTONES

  #define PCF8574_Pin0 254
  #define PCF8574_Pin1 253
  #define PCF8574_Pin2 251
  #define PCF8574_Pin3 247
  #define PCF8574_Pin4 239
  #define PCF8574_Pin5 223
  #define PCF8574_Pin6 191
  #define PCF8574_Pin7 127

  // especificación para los pines
  #define _LCDML_CONTROL_PCF8574_enable_quit    0
  #define _LCDML_CONTROL_PCF8574_enable_lr      0
  
  #define _LCDML_CONTROL_PCF8574_enter          PCF8574_Pin0
  #define _LCDML_CONTROL_PCF8574_up             PCF8574_Pin1
  #define _LCDML_CONTROL_PCF8574_down           PCF8574_Pin2
  #define _LCDML_CONTROL_PCF8574_left           PCF8574_Pin3
  #define _LCDML_CONTROL_PCF8574_right          PCF8574_Pin4
  #define _LCDML_CONTROL_PCF8574_quit           PCF8574_Pin5
// **********************************************************
void lcdml_menu_control(void)
{
  // Si algo debe iniciarse, colóquelo en la condición de configuración
  if(LCDML.BT_setup()) {
    // runs only once
  }

  if((millis() - g_LCDML_DISP_press_time) >= 200) {
      g_LCDML_DISP_press_time = millis(); // reset

    Wire.write(0xff); // todos son pines de entrada?
    Wire.requestFrom(PCF8574_1, 1);
   if (Wire.available()) {
    switch (Wire.read())
    {
      case _LCDML_CONTROL_PCF8574_enter:  LCDML.BT_enter(); break;
      case _LCDML_CONTROL_PCF8574_up:     LCDML.BT_up();    break;
      case _LCDML_CONTROL_PCF8574_down:   LCDML.BT_down();  break;
    #if(_LCDML_CONTROL_PCF8574_enable_quit == 1)
      case _LCDML_CONTROL_PCF8574_quit:   LCDML.BT_quit();  break;
    #endif
    
    #if(_LCDML_CONTROL_PCF8574_enable_lr   == 1)
      case _LCDML_CONTROL_PCF8574_left: LCDML.BT_left(); break;
      case _LCDML_CONTROL_PCF8574_right:   LCDML.BT_right();  break;
    #endif
    
      default: break;
    }
  }
 }
}
// *********************************************************************
// ******************************* FIN *********************************
// *********************************************************************


#else
  #error _LCDML_CONTROL_cfg is not defined or not in range
#endif
