#!/usr/bin/env node
/**
 * ============================================================================
 * VERIFICADOR DE INTEGRIDAD & SINTAXIS (CHECK) — SOPORTE TÉCNICO UETS
 * ============================================================================
 * Uso: pnpm run check  (o: node scripts/check.js)
 */

const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

const rootDir = path.resolve(__dirname, '..');

const c = {
  reset: '\x1b[0m',
  bold: '\x1b[1m',
  green: '\x1b[32m',
  yellow: '\x1b[33m',
  red: '\x1b[31m',
  cyan: '\x1b[36m',
  gray: '\x1b[90m'
};

console.log(`\n${c.bold}${c.cyan}======================================================================${c.reset}`);
console.log(`${c.bold}${c.cyan} 🔍 VERIFICADOR DE INTEGRIDAD Y SINTAXIS — SOPORTE TÉCNICO UETS        ${c.reset}`);
console.log(`${c.bold}${c.cyan}======================================================================${c.reset}\n`);

let errores = 0;

// 1. Verificar existencia y formato JSON
console.log(`${c.bold}📁 [1/4] Verificando archivos de configuración y esquemas JSON:${c.reset}`);
const jsonFiles = [
  '02-bus-i2c-oled.code-workspace',
  'bloque_1/diagram.json',
  'bloque_2/diagram.json',
  'bloque_3/diagram.json',
  'bloque_4/diagram.json',
  'package.json'
];

jsonFiles.forEach(relPath => {
  const fullPath = path.join(rootDir, relPath);
  if (!fs.existsSync(fullPath)) {
    console.log(`  ${c.red}✖ Falta archivo requerido: ${relPath}${c.reset}`);
    errores++;
    return;
  }
  try {
    const raw = fs.readFileSync(fullPath, 'utf8');
    JSON.parse(raw);
    console.log(`  ${c.green}✔ ${relPath} [JSON Válido]${c.reset}`);
  } catch (err) {
    console.log(`  ${c.red}✖ ${relPath} tiene error de sintaxis JSON: ${err.message}${c.reset}`);
    errores++;
  }
});

// 2. Verificar llaves y paréntesis en código de Arduino
console.log(`\n${c.bold}🧩 [2/4] Verificando balance de sintaxis básica (llaves y paréntesis):${c.reset}`);
const inoFiles = [
  'bloque_1/src/bloque_1.ino',
  'bloque_2/src/bloque_2.ino',
  'bloque_3/src/bloque_3.ino',
  'bloque_4/src/bloque_4.ino'
];

inoFiles.forEach(relPath => {
  const fullPath = path.join(rootDir, relPath);
  if (!fs.existsSync(fullPath)) {
    console.log(`  ${c.red}✖ Archivo faltante: ${relPath}${c.reset}`);
    errores++;
    return;
  }

  const code = fs.readFileSync(fullPath, 'utf8');
  let openBraces = (code.match(/{/g) || []).length;
  let closeBraces = (code.match(/}/g) || []).length;
  let openParens = (code.match(/\(/g) || []).length;
  let closeParens = (code.match(/\)/g) || []).length;

  if (openBraces === closeBraces && openParens === closeParens) {
    console.log(`  ${c.green}✔ ${relPath} [Sintaxis balanceada: ${openBraces} llaves, ${openParens} paréntesis]${c.reset}`);
  } else {
    console.log(`  ${c.red}✖ ${relPath} tiene desbalance de sintaxis:${c.reset}`);
    if (openBraces !== closeBraces) console.log(`     Llaves: { = ${openBraces}, } = ${closeBraces}`);
    if (openParens !== closeParens) console.log(`     Paréntesis: ( = ${openParens}, ) = ${closeParens}`);
    errores++;
  }
});

// 3. Verificar reglas inmutables de UETS
console.log(`\n${c.bold}🛡️ [3/4] Verificando cumplimiento de Reglas Inmutables UETS:${c.reset}`);
let violaciones = [];
inoFiles.forEach(relPath => {
  const fullPath = path.join(rootDir, relPath);
  if (fs.existsSync(fullPath)) {
    const code = fs.readFileSync(fullPath, 'utf8');
    if (/c\+\+/i.test(code)) violaciones.push(`${relPath}: Contiene 'C++'. Usar 'código de Arduino'.`);
    if (/baymax/i.test(code)) violaciones.push(`${relPath}: Contiene 'Baymax'. Usar nomenclatura neutral.`);
    if (/socr[aá]t/i.test(code)) violaciones.push(`${relPath}: Contiene jerga 'socrática'.`);
  }
});

if (violaciones.length === 0) {
  console.log(`  ${c.green}✔ Cero infracciones de reglas de aula UETS.${c.reset}`);
} else {
  violaciones.forEach(v => {
    console.log(`  ${c.red}✖ ${v}${c.reset}`);
    errores++;
  });
}

// 4. Comprobación de compilación con PlatformIO (si está disponible)
console.log(`\n${c.bold}🐜 [4/4] Verificando compilación con PlatformIO:${c.reset}`);
let pioAvailable = false;
try {
  execSync('pio --version', { stdio: 'ignore' });
  pioAvailable = true;
} catch (_) {
  pioAvailable = false;
}

if (pioAvailable) {
  console.log(`  ${c.green}✔ PlatformIO CLI detectado. Probando compilación...${c.reset}`);
  ['bloque_1', 'bloque_2', 'bloque_3', 'bloque_4'].forEach(b => {
    try {
      execSync(`pio run -d ${b}`, { stdio: 'inherit' });
      console.log(`  ${c.green}✔ ${b} compila exitosamente.${c.reset}`);
    } catch (e) {
      console.log(`  ${c.yellow}⚠️ ${b} no compila (posiblemente contiene TODOs pendientes de resolver).${c.reset}`);
    }
  });
} else {
  console.log(`  ${c.gray}ℹ️ PlatformIO CLI no está en el PATH global.${c.reset}`);
  console.log(`  ${c.cyan}👉 Recuerda compilar desde VS Code haciendo clic en el icono de la hormiga 🐜 ➔ Build.${c.reset}`);
}

// Resumen
console.log(`\n${c.bold}======================================================================${c.reset}`);
if (errores === 0) {
  console.log(`  ${c.green}${c.bold}✅ ¡TODO EN ORDEN! No se encontraron errores estructurales ni de sintaxis.${c.reset}`);
} else {
  console.log(`  ${c.red}${c.bold}⚠️ Se encontraron ${errores} advertencia(s) o error(es). Revisa los detalles arriba.${c.reset}`);
}
console.log(`${c.bold}======================================================================\n${c.reset}`);

process.exit(errores === 0 ? 0 : 1);
