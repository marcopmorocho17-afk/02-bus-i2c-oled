#include <Arduino.h>
#include <Wire.h>
#include "config.h"

void initI2CBus() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_CLOCK_SPEED);

    Serial.println("[I2C] Bus inicializado en SDA:GPIO21, SCL:GPIO22");
}

int scanI2CBus() {
    int devicesFound = 0;

    Serial.println("\n--- [I2C SCANNER] INICIANDO BARRIDO DE DIRECCIONES (0x01 .. 0x7F) ---");

    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();

        if (error == 0) {
            Serial.printf("[I2C] Dispositivo detectado en: 0x%02X ", address);
            if (address == OLED_I2C_ADDR) {
                Serial.println("➔ [Display OLED SSD1306] [OK]");
            } else {
                Serial.println("➔ [Periférico Desconocido]");
            }
            devicesFound++;
        }
    }

    if (devicesFound == 0) {
        Serial.println("[I2C] ❌ No se detectaron dispositivos en el bus.");
    } else {
        Serial.printf("--- [I2C SCANNER] FINALIZADO: %d dispositivo(s) encontrado(s) ---\n\n", devicesFound);
    }

    return devicesFound;
}
