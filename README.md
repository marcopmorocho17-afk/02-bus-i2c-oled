# ⚡ Starter-Kit: Taller Práctico Semana 02 — Soporte Técnico (3° BGU UETS)
### Protocolo Bus I2C, Scanner de Hardware y Telemetría en Pantalla OLED SSD1306

Bienvenido al taller práctico de la Semana 02. En este laboratorio desarrollarás el firmware modular en código de Arduino para inicializar la pantalla de telemetría y diagnóstico del **sistema embebido ESP32**.

---

## 📺 Guía Maestra Técnica en Vivo (Cloudflare Edge)

[![Ver Guía Maestra en Vivo](https://img.shields.io/badge/Guía_Técnica-Ver_en_Línea-E07A5F?style=for-the-badge&logo=cloudflare)](https://uets-st-portal.vgmiltonisaac.workers.dev/02-bus-i2c-oled/)

👉 **[Abrir Guía Maestra en el Portal Oficial (Cloudflare Edge)](https://uets-st-portal.vgmiltonisaac.workers.dev/02-bus-i2c-oled/)**  
👉 **[Ver Portal Curricular de Soporte Técnico](https://uets-st-portal.vgmiltonisaac.workers.dev/)**

---

## ❄️ Setup Diario Anti-Deep Freeze (Obligatorio en Laboratorio)

Dado que las computadoras del laboratorio se reinician a su estado base al apagarse, configura tu identidad de Git antes de empezar:

```bash
git config --global user.name "TU_USUARIO_GITHUB"
git config --global user.email "tu_correo_registrado@ejemplo.com"
```

### Flujo de Trabajo en Git:
1. Haz **Fork** del repositorio docente a tu cuenta personal de GitHub.
2. Clona tu propio fork en la máquina local:
   ```bash
   git clone https://github.com/MI_USUARIO_GITHUB/02-bus-i2c-oled.git
   cd 02-bus-i2c-oled
   ```
3. Crea tu rama de entrega personal:
   ```bash
   git checkout -b entrega/nombre-apellido
   ```

---

## 📖 Material de Apoyo Estudiantil
* 📘 **[Cheatsheet del Estudiante (Analogías & Código de Arduino)](CHEATSHEET_ESTUDIANTE.md):** Hoja de trucos con las analogías del megáfono, la pizarra borrador y preguntas clave de auto-diagnóstico.

---

## 🛠️ Arquitectura Modular del Proyecto (Pestañas .ino)

El código está estructurado en módulos `.ino` para trabajar con pestañas limpias en Arduino IDE / PlatformIO:

```text
02-bus-i2c-oled/
├── 02_Bus_I2C_OLED.code-workspace <-- Espacio de trabajo oficial para VS Code
├── CHEATSHEET_ESTUDIANTE.md        <-- Hoja de referencia técnica rápida
├── README.md                       <-- Guía de inicio y protocolo de aula
├── bloque_4_integrador.ino         <-- Orquestador principal (setup / loop)
├── config.h                        <-- Mapeo central de pines y direcciones I2C
├── i2c_bus.ino                     <-- Módulo de escaneo del bus (Reto 01)
├── oled_display.ino                <-- Controlador SSD1306 y logBoot() (Retos 02 y 03)
├── system_diagnostics.ino          <-- Rutina POST de auto-diagnóstico (Reto 04)
├── platformio.ini                  <-- Configuración de compilación ESP32
├── wokwi.toml                      <-- Configuración del simulador Wokwi
└── diagram.json                    <-- Conexiones visuales en Wokwi Simulator
```

---

## 🚀 Flujo de Trabajo en 5 Pasos

1. **Abrir Espacio de Trabajo:** En VS Code, ve a **Archivo ➔ Abrir espacio de trabajo desde archivo...** y selecciona `02_Bus_I2C_OLED.code-workspace`.
2. **Resolver los `// TODO:`:** Completa las funciones guiándote con el [Cheatsheet](CHEATSHEET_ESTUDIANTE.md) y la Guía Maestra Web.
3. **Simulación en Wokwi:** Abre `diagram.json` o presiona `F1` ➔ `Wokwi: Start Simulator`.
4. **Verificar Salidas:**
   - **Serial Monitor (115200 bps):** Scanner detectando `0x3C` [OK].
   - **Pantalla OLED:** Secuencia POST con tabla de estados alineada a la derecha y mensaje final `>> SISTEMA LISTO <<`.
5. **Entrega en GitHub:** Guarda tus commits semánticos y abre tu Pull Request comparando tu rama `entrega/nombre-apellido` contra la rama `base: main` del docente.

---

## ⏱️ Límites de Duración de Video & Penalizaciones

* **Short de Anticipación ($\le 60\text{ s}$):** Límite estricto de 60 segundos (margen de gracia hasta 65s). Penalización automática de **-0.50 pts** si excede los 65 segundos.
* **Screencast Demostrativo (3 a 4 min):** Límite máximo absoluto de **5:00 minutos**. La revisión docente se detiene en 5:00; videos de 5:01 en adelante tienen **-1.00 pt de penalización**.

---

## 🕊️ Directiva de Entrega Parcial Salesiana ("¡Nunca te quedes con 0!")

Si la clase concluye y no alcanzaste a terminar todos los retos:
1. Haz commit de tu avance: `git commit -m "feat: avance parcial hasta reto 02"`
2. Sube los cambios y abre el Pull Request.
3. Graba tu video screencast explicando lo que lograste implementar y tus aprendizajes.
4. **Beneficio:** Aseguras los **5.00 puntos de la sustentación oral** más la nota proporcional del circuito.
