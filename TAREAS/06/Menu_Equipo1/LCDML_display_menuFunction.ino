/* ===================================================================== *
 *                                                                       *
 * Menu Callback función                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * CÓDIGO EJEMPLO:

// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    //LCDML_UNUSED(param);
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);

    // uncomment this line when the menu should go back to the last called position
    // this could be a cursor position or the an active menu function
    // GBA means => go back advanced
    //LCDML.FUNC_setGBA() 

    //
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button or event status change

    // uncomment this line when the screensaver should not be called when this function is running
    // reset screensaver timer
    //LCDML.SCREEN_resetTimer();

    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
    // this function is always called when the functions ends.
    // this means when you are calling a jumpTo ore a goRoot function
    // that this part is called before a function is closed
  }
}


 * ===================================================================== *
 */


// *********************************************************************
void mFunc_information(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
  // elimina las advertencias del compilador cuando no se usa la variable param:
     LCDML_UNUSED(param);

    // setup función
    lcd.setCursor(0, 0);
    lcd.print(F("Aplicacion de menu"));
    lcd.setCursor(0, 1);
    lcd.print(F("Equipo 01"));
    lcd.setCursor(0, 2);
    lcd.print(F("Presione cualquier"));
    lcd.setCursor(0, 3);
    lcd.print(F("tecla"));
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
  // función de bucle, se puede ejecutar en un bucle cuando se establece LCDML_DISP_triggerMenu (xx)
// el botón de salir funciona en todas las funciones de DISP sin ningún control; inicia la función loop_end
    if(LCDML.BT_checkAny()) { // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
      // LCDML_goToMenu detiene una función de menú en ejecución y va al menú
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** FINAL ESTABLE*********
  {
    // aquí puede restablecer algunas variables globales o no hacer nada

  }
}


// *********************************************************************
uint8_t g_func_timer_info = 0;  // contador de tiempo (variable global)
unsigned long g_timer_1 = 0;    // contador de tiempo (variable global)
void mFunc_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // elimine las advertencias del compilador cuando no se use la variable param:
    LCDML_UNUSED(param);

    lcd.print(F("10 seg para salir")); // imprimir algo de contenido en la primera fila
    g_func_timer_info = 10;       // reiniciar y configurar el temporizador
    LCDML.FUNC_setLoopInterval(100);  // inicia un evento de activación para la función de bucle cada 100 milisegundos
    LCDML.TIMER_msReset(g_timer_1);
  }


  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // función de bucle, se puede ejecutar en un bucle cuando se establece LCDML_DISP_triggerMenu (xx)
    // el botón de salir funciona en todas las funciones de DISP sin ningún control; inicia la función loop_end


// reiniciar el temporizador del salvapantallas
    LCDML.SCREEN_resetTimer();

// esta función se llama cada 100 milisegundos

// este método comprueba cada 1000 milisegundos si se llama
    if(LCDML.TIMER_ms(g_timer_1, 1000)) {
      g_func_timer_info--;                // incrementar el valor cada segundo
      lcd.setCursor(0, 0);                // establecer posición del cursor
      lcd.print(F("  "));
      lcd.setCursor(0, 0);                // establecer posición del cursor
      lcd.print(g_func_timer_info);       // imprimir el valor del contador de tiempo
    }

    // esta función solo se puede finalizar cuando se presiona el botón de salida o se acaba el tiempo
    // verifica si la función termina normalmente
    if (g_func_timer_info <= 0)
    {
      // deja esta función
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // aquí puede restablecer algunas variables globales o no hacer nada
  }
}

void encendiendeled()//(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
// remmove las advertencias del compilador cuando no se usa la variable param:
    //LCDML_UNUSED(param);

    // setup function
    digitalWrite(led,HIGH);
     LCDML.FUNC_goBackToMenu();
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    //función de bucle, se puede ejecutar en un bucle cuando se establece LCDML_DISP_triggerMenu (xx)
// el botón de salir funciona en todas las funciones de DISP sin ningún control; inicia la función loop_end
    if(LCDML.BT_checkAny()) { //compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
      // LCDML_goToMenu detiene una función de menú en ejecución y va al menú
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    //aquí puede restablecer algunas variables globales o no hacer nada

  }
}
/////////////////////////////////////////////////////////////////////////
void apagaled()//(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
// remmove las advertencias del compilador cuando no se usa la variable param:
    //LCDML_UNUSED(param);

    // setup function
    digitalWrite(led,LOW);
     LCDML.FUNC_goBackToMenu();
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
// función de bucle, se puede ejecutar en un bucle cuando se establece LCDML_DISP_triggerMenu (xx)
// el botón de salir funciona en todas las funciones de DISP sin ningún control; inicia la función loop_end
    if(LCDML.BT_checkAny()) { //compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
     // LCDML_goToMenu detiene una función de menú en ejecución y va al menú
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    //aquí puede restablecer algunas variables globales o no hacer nada
  }
}
// *********************************************************************
uint8_t g_button_value = 0; // contador de valor de botón (variable global)
void mFunc_p2(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
// remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);

    // setup function
    // mostrar LCD contenido
    // mostrar LCD contenido
    lcd.setCursor(0, 0);
    lcd.print(F("selecciione cantidad"));
    lcd.setCursor(0, 1);
    lcd.print(F("de parpadeos"));
    // restaurar el valor del boton
    g_button_value = 0;

    // Desactive el protector de pantalla para esta función hasta que se cierre
    LCDML.FUNC_disableScreensaver();

  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // el botón de salir funciona en todas las funciones de DISP sin ningún control; inicia la función loop_end
    if (LCDML.BT_checkAny()) // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
    {
      if (LCDML.BT_checkDown()) // compruebe si se presiona el botón
      {
        LCDML.BT_resetDown(); // restablecer el botón izquierdo
        g_button_value++;

// actualizar el contenido de la pantalla LCD
// actualizar el contenido de la pantalla LCD
        lcd.setCursor(3, 2); // poner cursor
        lcd.print(g_button_value); // imprimir cambiar contenido
      }
      if (LCDML.BT_checkEnter()) {
      for (int cont=0; cont<g_button_value; cont++)
      {
         digitalWrite(led,HIGH);
         delay(500);
         digitalWrite(led,LOW);
          delay(500);
        }
      LCDML.FUNC_goBackToMenu();      // deja esta función
    }
    }

// comprobar si el número de botones es tres
    
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    //aquí puede restablecer algunas variables globales o no hacer nada
  }
}



// *********************************************************************
void mFunc_screensaver(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
// remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
// actualizar el contenido de la pantalla LCD
    lcd.setCursor(0, 0); // poner cursor
    lcd.print(F("temperatura:")); // imprimir cambiar contenido
    lcd.setCursor(12, 0); //  poner cursor
    lcd.print((temperature));
    lcd.setCursor(0, 1); //  poner cursor
    lcd.print(F("humedad:"));
    lcd.setCursor(12, 1); //  poner cursor
    lcd.print((humidity)); // imprimir cambiar contenido
    lcd.setCursor(0, 2); //  poner cursor
    lcd.print(F("cualquier tecla"));
    lcd.setCursor(0, 3); //  poner cursor
    lcd.print(F("para entrar menu"));
    LCDML.FUNC_setLoopInterval(100);  // inicia un evento de activación para la función de bucle cada 100 milisegundos
  }

  if(LCDML.FUNC_loop())
  {
    if (LCDML.BT_checkAny()) // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
    {
      LCDML.FUNC_goBackToMenu();  // deja esta función

    }
  }

  if(LCDML.FUNC_close())
  {
// El salvapantallas va al menú raíz
    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
// remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);

// finaliza la función y retrocede una capa
    LCDML.FUNC_goBackToMenu(1);      // deja esta función y retrocede una capa
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
// remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);

// ir a la raíz y mostrar el menú
    LCDML.MENU_goRoot();
  }
}


// *********************************************************************
void mFunc_jumpTo_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);
    
// Ir a la pantalla principal
    LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}
// *********************************************************************
void mFunc_jumpTo_lamp(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
// remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);
    
// Ir a la pantalla principal
    LCDML.OTHER_jumpToID(4);
  }
}
