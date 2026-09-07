#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

// Instanciación del objeto display con sus 4 parámetros clave:
// (Ancho, Alto, Referencia al bus Wire, Pin de Reset)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

bool initDisplay() {
    // TODO 2.1: Arrancar la pantalla OLED activando la bomba de carga interna (charge pump)
    // y pasando la dirección I2C (0x3C).
    // Pregunta Guía: ¿Qué constante activa la bomba de carga a ~7.5V y qué dirección usa el OLED?
    // if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
    //     Serial.println("[OLED] ERROR: No se detectó la pantalla en 0x3C");
    //     return false;
    // }

    // Limpieza inicial del cuaderno borrador en memoria RAM
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.display();
    
    Serial.println("[OLED] Pantalla SSD1306 inicializada exitosamente [OK]");
    return true;
}

void showBootHeader() {
    // TODO 2.2: Construir la cabecera visual de la estación de telemetría:
    // 1. Limpiar el borrador en memoria RAM con display.clearDisplay()
    // 2. Establecer tamaño de texto 1 y color SSD1306_WHITE
    // 3. Posicionar el cursor centrado en (X=8, Y=0) y escribir: ">> ESP32 SISTEMA <<"
    // 4. Dibujar una línea divisoria horizontal en Y=10 desde X=0 hasta X=128
    // 5. Dejar el cursor en (X=0, Y=14) listo para los módulos
    // 6. ¡Pregunta de Pizarra!: Si no ejecutas display.display(), ¿se verá algo en la pantalla?
    /* ESCRIBE TU CÓDIGO AQUÍ */
    
    // delay(400); // Pausa visual
}

void logBoot(const char* moduleName, bool isOk) {
    // TODO 3.1: Imprimir el nombre del módulo en la posición actual del cursor
    /* ESCRIBE TU CÓDIGO AQUÍ */

    // TODO 3.2: Alinear el estado [OK] o [ERR] a la derecha de la pantalla
    // Pregunta Guía: ¿Por qué usamos display.getCursorY() en vez de un número fijo en Y?
    // Pista: Salta a la columna X=95 en la misma fila vertical:
    // display.setCursor(95, display.getCursorY());
    /* ESCRIBE TU CÓDIGO AQUÍ */

    // TODO 3.3: Según el valor de isOk (true/false), imprimir "[OK]" o "[ERR]"
    /* ESCRIBE TU CÓDIGO AQUÍ */

    // TODO 3.4: Volcar los cambios del buffer a la pantalla física y pausar 200ms
    // display.display();
    // delay(200);
}

void showSystemReady() {
    // TODO 3.5: Dibujar línea divisoria inferior en Y=52 y texto centrado ">> SISTEMA LISTO <<"
    display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
    display.setCursor(10, 55);
    display.println(">> SISTEMA LISTO <<");
    display.display();
    Serial.println("\n[SISTEMA] Todos los componentes operativos. Estación lista.\n");
}
