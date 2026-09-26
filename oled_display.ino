#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

bool initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("[OLED] ERROR: No se detectó la pantalla en 0x3C");
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
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
    display.setCursor(0, 14);
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
    display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
    display.setCursor(10, 55);
    display.println(">> SISTEMA LISTO <<");
    display.display();
    Serial.println("\n[SISTEMA] Todos los componentes operativos. Estación lista.\n");
}
