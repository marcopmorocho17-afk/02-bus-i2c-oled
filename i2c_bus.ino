#include <Arduino.h>
#include <Wire.h>
#include "config.h"

void initI2CBus() {
    // TODO 1.1: Inicializar el bus I2C en los pines SDA y SCL del ESP32.
    // Pregunta Guía: ¿Qué función de la librería Wire recibe (SDA_PIN, SCL_PIN)?
    // Pista: Usa las constantes I2C_SDA_PIN e I2C_SCL_PIN de config.h.
    // Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    // TODO 1.2: Configurar la velocidad del reloj a 400kHz (Modo Rápido).
    // Pregunta Guía: ¿Qué función configura la frecuencia del bus?
    // Pista: Usa la constante I2C_CLOCK_SPEED de config.h.
    // Wire.setClock(I2C_CLOCK_SPEED);

    Serial.println("[I2C] Bus inicializado en SDA:GPIO21, SCL:GPIO22");
}

int scanI2CBus() {
    int devicesFound = 0;

    Serial.println("\n--- [I2C SCANNER] INICIANDO BARRIDO DE DIRECCIONES (0x01 .. 0x7F) ---");

    // TODO 1.3: Recorrer las direcciones válidas de 7 bits (del 1 al 126).
    // Pregunta Guía: ¿Por qué en el protocolo I2C de 7 bits recorremos desde 1 hasta menor a 127?
    for (byte address = 1; address < 127; address++) {
        
        // TODO 1.4: Tocar la puerta del periférico:
        // 1. Iniciar la transmisión hacia la dirección con Wire.beginTransmission(address)
        // 2. Finalizar la transmisión capturando el código de respuesta con Wire.endTransmission()
        /* ESCRIBE TU CÓDIGO AQUÍ */
        // Wire.beginTransmission(address);
        // byte error = Wire.endTransmission();

        // TODO 1.5: Evaluar la respuesta del periférico:
        // Pregunta Guía: ¿Qué valor numérico devuelve Wire.endTransmission() cuando el periférico responde con ACK (Presente)?
        // if (error == 0) {
        //     Serial.printf("[I2C] Dispositivo detectado en: 0x%02X ", address);
        //     if (address == OLED_I2C_ADDR) {
        //         Serial.println("➔ [Display OLED SSD1306] [OK]");
        //     } else {
        //         Serial.println("➔ [Periférico Desconocido]");
        //     }
        //     devicesFound++;
        // }
    }

    if (devicesFound == 0) {
        Serial.println("[I2C] ❌ No se detectaron dispositivos en el bus.");
    } else {
        Serial.printf("--- [I2C SCANNER] FINALIZADO: %d dispositivo(s) encontrado(s) ---\n\n", devicesFound);
    }

    return devicesFound;
}
