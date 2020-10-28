#include <SimpleDHT.h>
int pinDHT11 = 5;
int led=6;
SimpleDHT11 dht11(pinDHT11);
// ============================================================
//                     Menú: Equipo01
// ============================================================
// Descripción:
// Este ejemplo incluye la funcionalidad completa sobre algunas pestañas. 
// Todas las pestañas que comienzan con "LCDML_display_ .." generan una 
// salida en la pantalla / consola / ....
// ============================================================
// *********************************************************************
// Configuraciones:
// *********************************************************************
// Esta Linea de código se habilita para placas distintas a Arduino.
// Por ejemplo para ESP, STM, SAM o cualquier otra.

//#define _LCDML_cfg_use_ram 

// *********************************************************************
// Librerias
// *********************************************************************
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <LCDMenuLib2.h>

// *********************************************************************
// Configuraciones para LCDML 
// *********************************************************************
  // Configuracion de la LCD
  #define _LCDML_DISP_cols  20
  #define _LCDML_DISP_rows  4

  #define _LCDML_DISP_cfg_cursor                     0x7E   // Cursos
  #define _LCDML_DISP_cfg_scrollbar                  1      // Habilita la barra de dezplazamiento

  // LCD 
  // Para I2C hay muchas maneras de inicialización, algunas de ellas se enlistan aquí
  // Si las filas y columnas no estan configuradas aquí, deberán configurarse.
  //LiquidCrystal_I2C lcd(0x27);  // Se selecciona la dirección de la LCD por la I2C
  //LiquidCrystal_I2C lcd(0x27, BACKLIGHT_PIN, POSITIVE);  // Se selecciona la dirección de la LCD por la I2C
  LiquidCrystal_I2C lcd(0x27,_LCDML_DISP_cols,_LCDML_DISP_rows);
  //LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Se selecciona la dirección de la LCD por la I2C

  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // Barra de desplazamiento 
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // Barra de desplazamiento estado 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // Barra de desplazamiento estado 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // Barra de desplazamiento estado 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // Barra de desplazamiento botón
  };

// *********************************************************************
// Prototipos
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

// *********************************************************************
// Variables globales
// *********************************************************************


// *********************************************************************
// Objetos
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // Elemento principal del menú, (NO CAMBIAR)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISPLAY
// *********************************************************************
  // LCDML_0        => capa 0
  // LCDML_0_X      => capa 1
  // LCDML_0_X_X    => capa 2
  // LCDML_0_X_X_X  => capa 3
  // LCDML_0_...      => capa ...

  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)      Función del menú en pantalla

  LCDML_add         (0  , LCDML_0         , 1  , "Informacion"      , mFunc_information);       // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (1  , LCDML_0         , 2  , "Contador 10 seg"        , mFunc_timer_info);        // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (2  , LCDML_0         , 3  , "LED"             , NULL);                    // NULL = No hay función del menú
  LCDML_add         (3  , LCDML_0_3       , 1  , "Lampara"           , NULL);                    // NULL = No hay función del menú
  LCDML_add         (4  , LCDML_0_3_1     , 1  , "Encender LED"         , encendiendeled);                    // NULL = No hay función del menú
  LCDML_add         (5  , LCDML_0_3_1     , 2  , "Apagar Led"           , apagaled);                    // NULL = No hay función del menú
  LCDML_add         (6  , LCDML_0_3_1     , 3  , "Regresar"             , mFunc_back);              // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (7 , LCDML_0_3       , 2  , "Parpadeo"        , mFunc_p2);                // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (8 , LCDML_0_3       , 3  , "Regresar"             , mFunc_back);              // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (9 , LCDML_0         , 4  , "Atajos"          , NULL);                    // NULL = No hay función del menú
  LCDML_add         (10 , LCDML_0_4       , 1  , "ir a la raiz"       , mFunc_goToRootMenu);      // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (11 , LCDML_0_4       , 2  , "ir al contador", mFunc_jumpTo_timer_info); // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (12 , LCDML_0_4       , 3  , "ir a la lampara", mFunc_jumpTo_lamp); // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  LCDML_add         (13 , LCDML_0_4       , 4  , "Regresar"             , mFunc_back);              // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  //LCDML_add         (13 , LCDML_0         , 5  , "sin funcion"          , NULL);                    // NULL = No hay función del menú
  LCDML_add         (14 , LCDML_0         , 6  , "Salvapantallas"      , mFunc_screensaver);       // Esta función se encuentra en la pestaña "LCDML_display_menuFunction" 
  // ***TIP*** Intenta actualizar _LCDML_DISP_cnt cada que se agregue un elemento al menú.

  // conteo de los elementos del menú - id del ultimo elemento
  // Este valor deberia ser el mismo del ultimo elemento
  #define _LCDML_DISP_cnt    14

  // Creación del menú
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // ÇInicialización serial; solo se necesita si se utilizara el control por el serial
    Serial.begin(9600);                // velocidad en baudios
    Serial.println(F(_LCDML_VERSION)); // solo para ejemplos
    pinMode(led,OUTPUT);
    // LCD inicalización
    lcd.init();
    lcd.backlight();
    //lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);  // sAlgunos disposotivos necesitan esto para la inicialización


    // Caraceres de la barra de desplazamiento
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Configuraciones que se pueden usar

    // Habilitar cambio del menú
    LCDML.MENU_enRollover();

    // Habilitar protector de pantalla (función de menú de protector de pantalla, tiempo para activar en ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 10000); // establecido en 10 segundos
    //LCDML.SCREEN_disable();

    // Algunos métodos necesarios

    // Puede saltar a una función de menú desde cualquier lugar con
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // el parametro es el nombre de la función
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    LCDML.loop();
  }
