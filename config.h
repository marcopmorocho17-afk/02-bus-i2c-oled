#pragma once
#include <Arduino.h>

// ============================================================================
// UETS SOPORTE TÉCNICO — CONFIGURACIÓN GLOBAL DE HARDWARE (SEMANA 02)
// Sistema Embebido de Telemetría & Diagnóstico — ESP32 DevKit v4
// ============================================================================

// Configuración de Puerto Serial
#define SERIAL_BAUD 115200

// Configuración del Bus I2C
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_CLOCK_SPEED 400000 // 400 kHz (Fast Mode)

// Direcciones I2C de Periféricos (Hexadecimal de 7 bits)
#define OLED_I2C_ADDR 0x3C     // Pantalla OLED SSD1306 128x64
#define MPU6050_I2C_ADDR 0x68  // Giroscopio/Acelerómetro (Trimestre 1)
#define MAX30102_I2C_ADDR 0x57 // Pulsioxímetro SpO2/BPM (Trimestre 2)

// Parámetros de la Pantalla OLED SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET_PIN -1      // Compartido con el pin de reset del ESP32
