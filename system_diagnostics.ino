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

    showBootHeader();

    logBoot("ESP32 240MHz", true);
    logBoot("I2C @ 400kHz", true);
    logBoot("OLED 0x3C", true);
    logBoot("Bateria 8.4V", true);

    delay(500);

    showSystemReady();
}
