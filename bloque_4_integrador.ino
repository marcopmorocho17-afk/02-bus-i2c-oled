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

    initI2CBus();

    int dispositivos = scanI2CBus();
    bool displayReady = initDisplay();

    if (displayReady && dispositivos > 0) {
        runSystemPOST();
    } else {
        Serial.println("[SISTEMA] ERROR: No se pudo completar la inicialización del bus I2C o de la pantalla OLED.");
    }
}

void loop() {
    delay(1000);
}
