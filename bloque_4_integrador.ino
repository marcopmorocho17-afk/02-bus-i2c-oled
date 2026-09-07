#include <Arduino.h>
#include "config.h"

// Prototipos de funciones modularizadas en las otras pestañas .ino
void initI2CBus();
int scanI2CBus();
bool initDisplay();
void runSystemPOST();

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("\n[SISTEMA] Arrancando microcontrolador ESP32 DevKit v4...");

    // TODO 5.1: ¿Qué inicializamos primero? ¿El bus físico o los sensores?
    // Inicia el bus I2C invocando initI2CBus()
    /* ESCRIBE TU CÓDIGO AQUÍ */

    // TODO 5.2: Pasa lista en el bus invocando scanI2CBus() y guarda el resultado en una variable
    // int dispositivos = scanI2CBus();
    /* ESCRIBE TU CÓDIGO AQUÍ */

    // TODO 5.3: Si la pantalla se inicializa correctamente con initDisplay() Y dispositivos > 0:
    // Ejecuta la secuencia de diagnóstico runSystemPOST().
    // Si no, reporta un error por el Monitor Serial.
    /* ESCRIBE TU CÓDIGO AQUÍ */
}

void loop() {
    // La rutina de arranque (POST) corre una sola vez en setup().
    // En las siguientes semanas aquí recibiremos comandos de telemetría.
    delay(1000);
}
