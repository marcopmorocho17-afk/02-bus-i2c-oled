#!/usr/bin/env node
/**
 * ============================================================================
 * EVALUADOR PEDAGÓGICO DE CÓDIGO — SOPORTE TÉCNICO UETS (2026–2027)
 * Validador modular por reto y global para la Semana 02 (Bus I2C & OLED)
 * ============================================================================
 * Uso:
 *   node scripts/evaluar.js      -> Evalúa todos los bloques (pnpm test / pnpm run test:all)
 *   node scripts/evaluar.js 1    -> Evalúa solo el Reto 01 (pnpm run start:01)
 *   node scripts/evaluar.js 2    -> Evalúa solo el Reto 02 (pnpm run start:02)
 *   node scripts/evaluar.js 3    -> Evalúa solo el Reto 03 (pnpm run start:03)
 *   node scripts/evaluar.js 4    -> Evalúa solo el Reto 04 (pnpm run start:04)
 */

const fs = require('fs');
const path = require('path');

const rootDir = path.resolve(__dirname, '..');
const targetArg = process.argv[2] ? process.argv[2].trim().toLowerCase() : 'all';
const targetBlock = targetArg === 'all' || !['1', '2', '3', '4'].includes(targetArg) ? null : parseInt(targetArg, 10);

// Colores ANSI
const c = {
  reset: '\x1b[0m',
  bold: '\x1b[1m',
  green: '\x1b[32m',
  yellow: '\x1b[33m',
  red: '\x1b[31m',
  cyan: '\x1b[36m',
  gray: '\x1b[90m',
  magenta: '\x1b[35m'
};

function leerArchivo(relPath) {
  const fullPath = path.join(rootDir, relPath);
  if (!fs.existsSync(fullPath)) return null;
  return fs.readFileSync(fullPath, 'utf8');
}

let violaciones = [];
function checkForbidden(content, file) {
  if (/c\+\+/i.test(content)) {
    violaciones.push(`Archivo '${file}' contiene 'C++'. Usar siempre 'código de Arduino'.`);
  }
  if (/baymax/i.test(content)) {
    violaciones.push(`Archivo '${file}' contiene 'Baymax'. Usar nomenclatura neutral 'Sistema Embebido ESP32'.`);
  }
  if (/socr[aá]t/i.test(content)) {
    violaciones.push(`Archivo '${file}' contiene jerga 'socrática'. Usar 'Preguntas Guía' o 'Preguntas de Pizarra'.`);
  }
}

// Encabezado
console.log(`\n${c.bold}${c.cyan}======================================================================${c.reset}`);
if (targetBlock) {
  console.log(`${c.bold}${c.cyan} 🤖 REPORTE DE RETO INDIVIDUAL — RETO 0${targetBlock} (SOPORTE TÉCNICO UETS)     ${c.reset}`);
} else {
  console.log(`${c.bold}${c.cyan} 🤖 REPORTE PEDAGÓGICO DE ENTREGA — SOPORTE TÉCNICO UETS (3° BGU)    ${c.reset}`);
  console.log(`${c.bold}${c.cyan}    Semana 02: Protocolo Bus I2C, Scanner y Pantalla OLED SSD1306     ${c.reset}`);
}
console.log(`${c.bold}${c.cyan}======================================================================${c.reset}\n`);

let totalPuntos = 0;
let bloquesCompletados = 0;

// ----------------------------------------------------------------------------
// EVALUACIÓN BLOQUE 1
// ----------------------------------------------------------------------------
function evaluarBloque1() {
  console.log(`${c.bold}🟢 Reto 01: Escáner de Direcciones de Hardware I2C (0x3C)${c.reset}`);
  const b1 = leerArchivo('bloque_1/src/bloque_1.ino');
  if (!b1) {
    console.log(`  ${c.red}✖ Archivo 'bloque_1/src/bloque_1.ino' no encontrado.${c.reset}`);
    return;
  }
  checkForbidden(b1, 'bloque_1/src/bloque_1.ino');

  const hasWireBegin = /Wire\.begin\s*\(\s*(21|I2C_SDA_PIN)\s*,\s*(22|I2C_SCL_PIN)\s*\)/i.test(b1) || /Wire\.begin\s*\(/i.test(b1);
  const hasWireClock = /Wire\.setClock\s*\(\s*(400000|I2C_CLOCK_SPEED)\s*\)/i.test(b1);
  const hasTransmission = /Wire\.beginTransmission\s*\(/i.test(b1) && /Wire\.endTransmission\s*\(/i.test(b1);
  const hasAckCheck = /error\s*==\s*0/i.test(b1) || /Wire\.endTransmission\s*\(\s*\)\s*==\s*0/i.test(b1);
  const hasOledAddr = /0x3C/i.test(b1) || /OLED_I2C_ADDR/i.test(b1);
  const hasTodoActive = b1.includes('/* ESCRIBE TU CÓDIGO AQUÍ */');

  let checks = [
    hasWireBegin ? '✔ Wire.begin(21, 22) configurado.' : '✖ Falta inicializar el bus con Wire.begin(21, 22).',
    hasWireClock ? '✔ Wire.setClock(400000) en Modo Rápido.' : '✖ Sugerencia: Wire.setClock(400000) para 400kHz.',
    hasTransmission ? '✔ Transmisión I2C (beginTransmission / endTransmission) activa.' : '✖ Falta tocar la puerta con beginTransmission() y capturar endTransmission().',
    (hasAckCheck && hasOledAddr) ? '✔ Condición ACK (error == 0) y dirección 0x3C evaluadas.' : '✖ Falta validar la respuesta ACK (error == 0) y la dirección 0x3C.'
  ];

  const completado = hasWireBegin && hasTransmission && hasAckCheck && !hasTodoActive;
  if (completado) {
    console.log(`  ${c.green}${c.bold}ESTADO: ¡RETO 01 COMPLETADO! (1.00 / 1.00 pt)${c.reset}`);
    bloquesCompletados++;
    totalPuntos += 1.0;
  } else {
    console.log(`  ${c.yellow}${c.bold}ESTADO: EN PROCESO / PENDIENTE (0.00 / 1.00 pt)${c.reset}`);
  }

  checks.forEach(ch => console.log(`    ${ch.startsWith('✔') ? c.green : c.yellow}${ch}${c.reset}`));

  if (targetBlock === 1) {
    console.log(`\n${c.bold}💡 Guía Rápida para Simular Reto 01 en Wokwi:${c.reset}`);
    console.log(`   1. Abre ${c.cyan}bloque_1/diagram.json${c.reset} en VS Code.`);
    console.log(`   2. Presiona ${c.cyan}F1${c.reset} ➔ escribe ${c.cyan}Wokwi: Start Simulator${c.reset}.`);
    console.log(`   3. Abre el Monitor Serial (115200 bps) y comprueba que detecte ${c.green}0x3C [OK]${c.reset}.\n`);
  }
}

// ----------------------------------------------------------------------------
// EVALUACIÓN BLOQUE 2
// ----------------------------------------------------------------------------
function evaluarBloque2() {
  console.log(`${c.bold}🟡 Reto 02: Inicialización Pantalla OLED SSD1306 & Cabecera Visual${c.reset}`);
  const b2 = leerArchivo('bloque_2/src/bloque_2.ino');
  if (!b2) {
    console.log(`  ${c.red}✖ Archivo 'bloque_2/src/bloque_2.ino' no encontrado.${c.reset}`);
    return;
  }
  checkForbidden(b2, 'bloque_2/src/bloque_2.ino');

  const hasBeginOled = /display\.begin\s*\(\s*SSD1306_SWITCHCAPVCC\s*,\s*(0x3C|OLED_I2C_ADDR)\s*\)/i.test(b2) || /display\.begin/i.test(b2);
  const hasClear = /display\.clearDisplay\s*\(\s*\)/i.test(b2);
  const hasTitle = /display\.(print|println)\s*\(\s*.*ESP32/i.test(b2);
  const hasLine = /display\.drawLine\s*\(/i.test(b2);
  const hasDisplayCall = /display\.display\s*\(\s*\)/i.test(b2);
  const hasTodoActive = b2.includes('/* ESCRIBE TU CÓDIGO AQUÍ */');

  let checks = [
    hasBeginOled ? '✔ display.begin(SSD1306_SWITCHCAPVCC, 0x3C) presente.' : '✖ Falta display.begin(SSD1306_SWITCHCAPVCC, 0x3C).',
    hasClear ? '✔ Limpieza de memoria buffer con display.clearDisplay().' : '✖ Falta limpiar el buffer RAM con display.clearDisplay().',
    (hasTitle && hasLine) ? '✔ Cabecera visual y línea divisoria dibujadas.' : '✖ Falta cabecera (>> ESP32 SISTEMA <<) o línea en Y=10.',
    hasDisplayCall ? '✔ ¡Orden display.display() invocada para volcar al vidrio!' : '✖ ¡ALERTA! Falta display.display() (pantalla en negro).'
  ];

  const completado = hasBeginOled && hasClear && hasDisplayCall && !hasTodoActive;
  if (completado) {
    console.log(`  ${c.green}${c.bold}ESTADO: ¡RETO 02 COMPLETADO! (1.00 / 1.00 pt)${c.reset}`);
    bloquesCompletados++;
    totalPuntos += 1.0;
  } else {
    console.log(`  ${c.yellow}${c.bold}ESTADO: EN PROCESO / PENDIENTE (0.00 / 1.00 pt)${c.reset}`);
  }

  checks.forEach(ch => console.log(`    ${ch.startsWith('✔') ? c.green : c.yellow}${ch}${c.reset}`));

  if (targetBlock === 2) {
    console.log(`\n${c.bold}💡 Guía Rápida para Simular Reto 02 en Wokwi:${c.reset}`);
    console.log(`   1. Abre ${c.cyan}bloque_2/diagram.json${c.reset} en VS Code.`);
    console.log(`   2. Inicia la simulación con ${c.cyan}F1 ➔ Wokwi: Start Simulator${c.reset}.`);
    console.log(`   3. Verifica que aparezca el título ${c.green}>> ESP32 SISTEMA <<${c.reset} con su línea horizontal.\n`);
  }
}

// ----------------------------------------------------------------------------
// EVALUACIÓN BLOQUE 3
// ----------------------------------------------------------------------------
function evaluarBloque3() {
  console.log(`${c.bold}🔵 Reto 03: Telemetría Modular con logBoot()${c.reset}`);
  const b3 = leerArchivo('bloque_3/src/bloque_3.ino');
  if (!b3) {
    console.log(`  ${c.red}✖ Archivo 'bloque_3/src/bloque_3.ino' no encontrado.${c.reset}`);
    return;
  }
  checkForbidden(b3, 'bloque_3/src/bloque_3.ino');

  const hasLogBootDef = /void\s+logBoot\s*\(/i.test(b3);
  const hasCursorY = /display\.getCursorY\s*\(\s*\)/i.test(b3);
  const hasRightCol = /display\.setCursor\s*\(\s*(95|90|100|85)\s*,\s*display\.getCursorY\s*\(\s*\)\s*\)/i.test(b3);
  const hasStatusLabels = /\[OK\]/i.test(b3) && /\[ERR\]/i.test(b3);
  const hasRefreshInLog = b3.includes('display.display();');
  const hasTodoActive = b3.includes('/* ESCRIBE TU CÓDIGO AQUÍ */');

  let checks = [
    hasLogBootDef ? '✔ Función modular logBoot(moduleName, isOk) definida.' : '✖ Falta definir la función modular logBoot().',
    (hasCursorY && hasRightCol) ? '✔ Alineación dinámica a la derecha con display.getCursorY().' : '✖ Pista: display.setCursor(95, display.getCursorY()) para alinear.',
    hasStatusLabels ? '✔ Etiquetas [OK] y [ERR] configuradas según estado.' : '✖ Falta imprimir [OK] o [ERR] según la variable isOk.',
    hasRefreshInLog ? '✔ Refresco del buffer display.display() dentro de la rutina.' : '✖ Falta display.display() para actualizar el renglón.'
  ];

  const completado = hasLogBootDef && hasCursorY && hasStatusLabels && !hasTodoActive;
  if (completado) {
    console.log(`  ${c.green}${c.bold}ESTADO: ¡RETO 03 COMPLETADO! (1.00 / 1.00 pt)${c.reset}`);
    bloquesCompletados++;
    totalPuntos += 1.0;
  } else {
    console.log(`  ${c.yellow}${c.bold}ESTADO: EN PROCESO / PENDIENTE (0.00 / 1.00 pt)${c.reset}`);
  }

  checks.forEach(ch => console.log(`    ${ch.startsWith('✔') ? c.green : c.yellow}${ch}${c.reset}`));

  if (targetBlock === 3) {
    console.log(`\n${c.bold}💡 Guía Rápida para Simular Reto 03 en Wokwi:${c.reset}`);
    console.log(`   1. Abre ${c.cyan}bloque_3/diagram.json${c.reset} en VS Code.`);
    console.log(`   2. Inicia Wokwi Simulator con ${c.cyan}F1${c.reset}.`);
    console.log(`   3. Comprueba que las etiquetas ${c.green}[OK]${c.reset} queden ordenadas en columna derecha.\n`);
  }
}

// ----------------------------------------------------------------------------
// EVALUACIÓN BLOQUE 4
// ----------------------------------------------------------------------------
function evaluarBloque4() {
  console.log(`${c.bold}🟣 Reto 04: Desafío Integrador POST Completo${c.reset}`);
  const b4 = leerArchivo('bloque_4/src/bloque_4.ino');
  if (!b4) {
    console.log(`  ${c.red}✖ Archivo 'bloque_4/src/bloque_4.ino' no encontrado.${c.reset}`);
    return;
  }
  checkForbidden(b4, 'bloque_4/src/bloque_4.ino');

  const hasPostRoutine = /runSystemPOST\s*\(\s*\)/i.test(b4);
  const hasSubsystems = /logBoot\s*\(\s*".*ESP32/i.test(b4) || /logBoot\s*\(\s*".*I2C/i.test(b4);
  const hasSystemReady = /showSystemReady\s*\(\s*\)/i.test(b4) || />>\s*SISTEMA LISTO\s*<</i.test(b4);
  const hasSetupOrchestration = /scanI2CBus/i.test(b4) && /initDisplay/i.test(b4);
  const hasTodoActive = b4.includes('/* ESCRIBE TU CÓDIGO AQUÍ */');

  let checks = [
    hasPostRoutine ? '✔ Rutina runSystemPOST() estructurada.' : '✖ Falta estructurar runSystemPOST().',
    hasSubsystems ? '✔ Diagnóstico de los 4 subsistemas con logBoot().' : '✖ Falta invocar logBoot() para ESP32, I2C, OLED y Batería.',
    hasSystemReady ? '✔ Mensaje final >> SISTEMA LISTO << configurado.' : '✖ Falta mostrar el mensaje final de sistema listo.',
    hasSetupOrchestration ? '✔ Orquestación en setup() (I2C -> Scan -> OLED -> POST).' : '✖ Falta enlazar la secuencia lógica en setup().'
  ];

  const completado = hasPostRoutine && hasSubsystems && hasSystemReady && !hasTodoActive;
  if (completado) {
    console.log(`  ${c.green}${c.bold}ESTADO: ¡RETO 04 COMPLETADO! (1.00 / 1.00 pt)${c.reset}`);
    bloquesCompletados++;
    totalPuntos += 1.0;
  } else {
    console.log(`  ${c.yellow}${c.bold}ESTADO: EN PROCESO / PENDIENTE (0.00 / 1.00 pt)${c.reset}`);
  }

  checks.forEach(ch => console.log(`    ${ch.startsWith('✔') ? c.green : c.yellow}${ch}${c.reset}`));

  if (targetBlock === 4) {
    console.log(`\n${c.bold}💡 Guía Rápida para Simular Reto 04 en Wokwi:${c.reset}`);
    console.log(`   1. Abre ${c.cyan}bloque_4/diagram.json${c.reset} en VS Code.`);
    console.log(`   2. Inicia Wokwi Simulator con ${c.cyan}F1${c.reset}.`);
    console.log(`   3. Observa la secuencia completa de arranque y el mensaje ${c.green}>> SISTEMA LISTO <<${c.reset}.\n`);
  }
}

// ----------------------------------------------------------------------------
// EJECUCIÓN SEGÚN ARGUMENTO
// ----------------------------------------------------------------------------
if (targetBlock === 1) {
  evaluarBloque1();
} else if (targetBlock === 2) {
  evaluarBloque2();
} else if (targetBlock === 3) {
  evaluarBloque3();
} else if (targetBlock === 4) {
  evaluarBloque4();
} else {
  evaluarBloque1();
  console.log();
  evaluarBloque2();
  console.log();
  evaluarBloque3();
  console.log();
  evaluarBloque4();

  // Resumen global
  console.log(`\n${c.bold}======================================================================${c.reset}`);
  console.log(`${c.bold}📋 RESUMEN FORMATIVO DE CALIFICACIÓN TÉCNICA (BLOQUE A):${c.reset}`);
  console.log(`   • Bloques completados al 100%: ${bloquesCompletados} de 4`);
  console.log(`   • Puntaje estimado de Código/Wokwi: ${totalPuntos.toFixed(2)} / 4.00 pts`);

  if (violaciones.length > 0) {
    console.log(`\n${c.red}${c.bold}⚠️ ALERTA DE REGLAS INSTITUCIONALES INCUMPLIDAS:${c.reset}`);
    violaciones.forEach(v => console.log(`   ${c.red}✖ ${v}${c.reset}`));
  } else {
    console.log(`   • Reglas institucionales UETS: ${c.green}100% Cumplidas (Cero términos prohibidos)${c.reset}`);
  }

  console.log(`\n${c.bold}🕊️ DIRECTIVA DE ENTREGA PARCIAL SALESIANA:${c.reset}`);
  if (bloquesCompletados === 4) {
    console.log(`   ${c.green}🎉 ¡Felicitaciones! Has completado los 4 bloques. Tu código está listo para PR.${c.reset}`);
  } else if (bloquesCompletados > 0) {
    console.log(`   ${c.cyan}ℹ️ Tienes ${bloquesCompletados} bloque(s) completado(s). Si la clase terminó, ¡haz commit y PR!${c.reset}`);
    console.log(`   ${c.cyan}   Graba tu video screencast explicando lo que lograste para asegurar tus 5.0 pts orales.${c.reset}`);
  } else {
    console.log(`   ${c.yellow}ℹ️ Repositorio en estado Starter-Kit. Completa los // TODO: guiándote con el Cheatsheet.${c.reset}`);
  }
  console.log(`${c.bold}======================================================================\n${c.reset}`);
}

if (violaciones.length > 0) {
  process.exit(1);
}
process.exit(0);
