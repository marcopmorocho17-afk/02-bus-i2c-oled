#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

#ifndef SERIAL_BAUD
  #define SERIAL_BAUD 115200
#endif

#ifndef I2C_SDA_PIN
  #define I2C_SDA_PIN 21
#endif

#ifndef I2C_SCL_PIN
  #define I2C_SCL_PIN 22
#endif

#ifndef I2C_CLOCK_SPEED
  #define I2C_CLOCK_SPEED 400000
#endif

#ifndef OLED_I2C_ADDR
  #define OLED_I2C_ADDR 0x3C
#endif

#ifndef SCREEN_WIDTH
  #define SCREEN_WIDTH 128
#endif

#ifndef SCREEN_HEIGHT
  #define SCREEN_HEIGHT 64
#endif

#ifndef OLED_RESET_PIN
  #define OLED_RESET_PIN -1
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void initI2CBus();
int scanI2CBus();
bool initDisplay();
void showBootHeader();
void logBoot(const char* moduleName, bool isOk);
void showSystemReady();

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("\n[SISTEMA] Arrancando microcontrolador ESP32 DevKit v4...");

    initI2CBus();

    int dispositivos = scanI2CBus();

    bool displayOk = initDisplay();
    
    if (displayOk && dispositivos > 0) {
        Serial.println("[SISTEMA] Hardware verificado. Iniciando secuencia POST...");
        
        showBootHeader();
        
        logBoot("I2C Bus", true);
        logBoot("OLED Disp", true);
        logBoot("Sensors", dispositivos > 1 ? true : false); 
        
        showSystemReady();
    } else {
        Serial.println("[SISTEMA] ERROR: POST cancelado por falta de perifericos o pantalla OLED.");
    }
}

void loop() {
    delay(1000);
}

void initI2CBus() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    Wire.setClock(I2C_CLOCK_SPEED);

    Serial.printf("[I2C] Bus inicializado en SDA: GPIO %d, SCL: GPIO %d a %d Hz\n", I2C_SDA_PIN, I2C_SCL_PIN, I2C_CLOCK_SPEED);
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
                Serial.println("➔ [Periferico Desconocido]");
            }
            devicesFound++;
        }
        else if (error == 4) {
            Serial.printf("[I2C] Error desconocido en la direccion: 0x%02X\n", address);
        }
        delay(5);
    }

    if (devicesFound == 0) {
        Serial.println("[I2C] ❌ No se detectaron dispositivos en el bus.");
    } else {
        Serial.printf("--- [I2C SCANNER] FINALIZADO: %d dispositivo(s) encontrado(s) ---\n\n", devicesFound);
    }

    return devicesFound;
}

bool initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR, true, false)) {
        Serial.println("[OLED] ERROR: No se detecto la pantalla.");
        return false;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.display();
    
    Serial.println("[OLED] Pantalla SSD1306 inicializada exitosamente [OK]");
    return true;
}

void showBootHeader() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(8, 0);
    display.println(">> ESP32 SISTEMA <<");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 12);
    display.display();
}

void logBoot(const char* moduleName, bool isOk) {
    display.print(moduleName);
    display.setCursor(95, display.getCursorY());

    if (isOk) {
        display.println("[OK]");
    } else {
        display.println("[ERR]");
    }

    display.display();
    delay(200);
}

void showSystemReady() {
    display.drawLine(0, 52, 127, 52, SSD1306_WHITE);
    display.setCursor(10, 55);
    display.println(">> SISTEMA LISTO <<");
    display.display();
    Serial.println("\n[SISTEMA] Todos los componentes operativos. Estacion lista.\n");
}
