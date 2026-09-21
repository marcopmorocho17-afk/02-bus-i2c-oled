#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

#ifndef SERIAL_BAUD
  #define SERIAL_BAUD 115200
#endif

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

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
    Serial.println("[I2C] Inicializando bus fisico de forma estricta (SDA: GPIO 21, SCL: GPIO 22)...");
    
    Wire.begin(21, 22); 
    
    Wire.setClock(100000); 
    delay(100);
}

int scanI2CBus() {
    Serial.println("[I2C] Escaneando dispositivos en el bus...");
    byte error, address;
    int nDevices = 0;

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            nDevices++;
            Serial.print("[I2C] -> ¡Dispositivo encontrado en la direccion: 0x");
            if (address < 16) Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("!");
        }
        delay(10);
    }
    return nDevices; 
}

bool initDisplay() {
    Serial.println("[DISPLAY] Localizando e inicializando pantalla OLED...");
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, true, false)) {
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
    Serial.println("[POST] Ejecutando diagnostico del sistema... TODO OK");
    
    display.clearDisplay();
    
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("SISTEMA OK");
    
    display.setTextSize(1);
    display.setCursor(0, 28);
    display.println("Hardware verificado");
    display.setCursor(0, 42);
    display.println("ESP32 DevKit v4");
    display.setCursor(0, 54);
    display.println("POST: EXITOSO");
    
    display.display(); 
}
