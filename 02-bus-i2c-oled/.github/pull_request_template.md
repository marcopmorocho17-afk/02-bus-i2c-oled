## 📋 Identificación del Estudiante
- **Nombre y Apellido:** <!-- Escribe tu nombre completo aquí -->
- **Curso y Especialidad:** 3° de Bachillerato General Unificado Técnico en Informática
- **Paralelo:** [ ] 3E1  |  [ ] 3E2
- **Rama de Entrega Personal:** `entrega/nombre-apellido`

---

## 🛠️ Bloque A: Circuito & Código de Arduino en Wokwi (50% · 5.0 Puntos)

### Checklist de Bloques Técnicos:
- [ ] **🟢 Bloque 1 (`bloque_1/src/bloque_1.ino`):** Scanner I2C implementado con `Wire.beginTransmission()` y `Wire.endTransmission()`. Detecta la dirección hexadecimal `0x3C` [OK].
- [ ] **🟡 Bloque 2 (`bloque_2/src/bloque_2.ino`):** Inicialización de pantalla SSD1306 con bomba de carga en `0x3C` y renderizado de cabecera visual con línea divisoria.
- [ ] **🔵 Bloque 3 (`bloque_3/src/bloque_3.ino`):** Función modular `logBoot()` con alineación dinámica a la derecha usando `display.getCursorY()`.
- [ ] **🟣 Bloque 4 (`bloque_4/src/bloque_4.ino`):** Secuencia integradora POST secuencial de los 4 subsistemas y mensaje final `>> SISTEMA LISTO <<`.
- [ ] **Compilación limpia:** Sin errores en PlatformIO / Wokwi Simulator en los bloques completados.
- [ ] **Commits Semánticos:** Commits estructurados respetando la convención (`feat:`, `fix:`, `refactor:`, `docs:`).

---

## 🎙️ Bloque B: Screencast Demostrativo Oral (50% · 5.0 Puntos)

- **Enlace al Video Screencast:** <!-- Pega aquí tu enlace de YouTube (No Listado), Google Drive Institucional o Loom -->
- **Duración del Video:** <!-- Indicar tiempo exacto mm:ss (Ejemplo: 03:45) -->

### Checklist del Video Screencast:
- [ ] **Duración reglamentaria:** Video de 3 a 4 minutos (Tope máximo absoluto: 5:00 min. Videos $\ge$ 5:01 min tienen penalización automática de -1.00 pt).
- [ ] **Cámara y Rostro:** Rostro del estudiante visible en todo momento mediante cámara web.
- [ ] **Voz y Sustentación Técnica:** Explicación fluida y técnica de las líneas SDA (`GPIO21`), SCL (`GPIO22`), la dirección `0x3C` y la memoria buffer del SSD1306.
- [ ] **Demostración en Vivo:** Monitor Serial a 115200 bps corriendo en vivo a la par de la pantalla OLED en el simulador Wokwi.

---

## 🕊️ Directiva de Entrega Parcial Salesiana ("¡Nunca te quedes con 0!")
- [ ] ¿Esta entrega es un avance parcial? En caso afirmativo, describe brevemente hasta qué bloque completaste y explica tus aprendizajes en el video screencast para asegurar tus puntos orales.
