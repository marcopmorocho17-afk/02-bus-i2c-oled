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
  #define I2C_CLOCK_SPEED 100000
#endif

#ifndef OLED_I2C_ADDR
  #define OLED_I2C_ADDR 0x3C
#endif

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initI2CBus();
int scanI2CBus();
bool initDisplay();
void runSystemPOST();

void setup() {
    Serial.begin(SERIAL_BAUD);
    
    delay(2000); 
    Serial.println("\n[SISTEMA] Arrancando microcontrolador ESP32 DevKit v4...");

    initI2CBus();
    delay(200);

    int dispositivos = scanI2CBus();
    Serial.print("[SISTEMA] Dispositivos totales detectados en el bus I2C: ");
    Serial.println(dispositivos);

    bool displayOk = initDisplay();
    
    if (displayOk && dispositivos > 0) {
        Serial.println("[SISTEMA] Hardware verificado con exito. Iniciando secuencia POST...");
        runSystemPOST();
    } else {
        Serial.println("[SISTEMA] ERROR: POST cancelado por falta de perifericos o pantalla OLED.");
    }
}

void loop() {
    delay(1000);
}

void initI2CBus() {
    Serial.printf("[I2C] Inicializando bus fisico en pines (SDA: GPIO %d, SCL: GPIO %d)...\n", I2C_SDA_PIN, I2C_SCL_PIN);
    
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN); 
    
    Wire.setClock(I2C_CLOCK_SPEED); 
    delay(100);
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
    Serial.println("[DISPLAY] Localizando e inicializando pantalla OLED...");
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR, true, false)) {
        Serial.println("[DISPLAY] ERROR: No se encontro un controlador SSD1306 valido.");
        return false;
    }
    
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.display(); 
    
    Serial.println("[DISPLAY] Pantalla OLED enlazada con exito.");
    return true;
}

void runSystemPOST() {
    Serial.println("[POST] Mostrando diagnostico oficial del sistema... OK");
    
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("SISTEMA OK");
    
    display.setTextSize(1);
    display.setCursor(0, 26);
    display.println("POST: Completado");
    display.setCursor(0, 38);
    display.println("ESP32 DevKit v4");
    display.setCursor(0, 50);
    display.println("Bus I2C: Operacional");
    
    display.display(); 
}
