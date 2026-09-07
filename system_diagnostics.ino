#include <Arduino.h>
#include "config.h"

// Prototipos de funciones implementadas en oled_display.ino
void showBootHeader();
void logBoot(const char* moduleName, bool isOk);
void showSystemReady();

void runSystemPOST() {
    Serial.println("\n==========================================");
    Serial.println("   ESP32: POWER-ON SELF TEST (POST)       ");
    Serial.println("==========================================");

    // TODO 4.1: Mostrar la cabecera del sistema invocando showBootHeader()
    /* ESCRIBE TU CÓDIGO AQUÍ */

    // TODO 4.2: Probar secuencialmente los 4 subsistemas de la estación usando logBoot(nombre, estado):
    // 1. "ESP32 240MHz"  -> true
    // 2. "I2C @ 400kHz"  -> true
    // 3. "OLED 0x3C"     -> true
    // 4. "Bateria 8.4V"  -> true
    // Pregunta Guía: ¿Qué ventaja tiene usar una función logBoot() frente a repetir 15 líneas de código por módulo?
    /* ESCRIBE TU CÓDIGO AQUÍ */

    delay(500);

    // TODO 4.3: Concluir la rutina mostrando el mensaje de sistema operativo invocando showSystemReady()
    /* ESCRIBE TU CÓDIGO AQUÍ */
}
