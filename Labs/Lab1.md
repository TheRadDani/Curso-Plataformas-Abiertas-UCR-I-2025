# Universidad de Costa Rica
# Facultad de Ingeniería
# Escuela Ingeniería Eléctrica
# IE-0117 Programación Bajo Plataformas Abiertas

# Profesor: Ing. Luis Daniel Ferreto Chavarría

<div style="display: flex; justify-content: space-between; align-items: center;">
  <img src="../images/ucr.png" alt="UCR Logo" style="width: 45%;"/>
  <img src="../images/eie.png" alt="EIE Logo" style="width: 45%;"/>
</div>

# Laboratorio 1: Monitoreo de Procesos y Análisis de Logs en GNU/Linux
**Fecha de Entrega:** 6 de abril, 12:00 pm  
**Modalidad de Entrega:** Repositorio de GitHub (compartir enlace con el profesor)  
**Laboratorio individual**  
---

## Objetivo  
Desarrollar un script en Bash que monitoree un proceso específico, analice sus estadísticas de memoria y genere un reporte automático. Este laboratorio integra conceptos de gestión de procesos, manipulación de archivos y uso de herramientas CLI.

---

## Descripción del Problema  

Imagina que trabajas como administrador de sistemas y debes garantizar que un servicio crítico (por ejemplo, `gedit`) funcione correctamente. Para ello, necesitas:  

1. **Monitorear el proceso**: Obtener su PID, uso de memoria y tiempo de ejecución.  
2. **Generar un log (<archivo>.log)**: Registrar cada 10 segundos el estado del proceso.  
3. **Crear un reporte de formato .md**: Al finalizar, mostrar un resumen con:  
   - Máximo y mínimo uso de memoria.  
   - Tiempo total de monitoreo.  
   - Promedio de uso de memoria.  

Si el proceso se detiene, el script debe finalizar y guardar el motivo en el reporte.  

---

## Requisitos Técnicos  

### 1. Script en Bash (`monitor.sh`)  
- Debe aceptar el nombre del proceso como argumento (ej: `./monitor.sh gedit`).  
- Usar comandos como `ps`, `grep`, `awk`, y `date` para extraer datos.  
- Guardar logs en `/tmp/process_monitor.log`.  
- Generar un reporte en `/tmp/process_report.md`.  

### 2. Archivo Explicativo (`README.md`)  
- Explicar cómo funciona el script.  
- Incluir capturas de pantalla y ejemplos de uso.  
- Describir cómo se abordan posibles errores (ej: proceso no existe).  

---

## Guías Clave para la Solución  
### 🔑 Pistas y Consejos Técnicos:
1. **Obtener el PID**:  
   - Usa `pgrep -o <nombre>` para obtener el PID del proceso.  
   - Ejemplo: `PID=$(pgrep -o "$1")`.  
   - Verifica si el PID existe con `[ -z "$PID" ]`.  

2. **Extraer estadísticas**:  
   - Para memoria: `ps -p "$PID" -o rss=`.  
   - Para tiempo de ejecución: `ps -p $PID -o etime --no-headers`.  
   - Usa `awk` para formatear decimales: `awk '{printf "%.1f", $1}'`. 
   - Convertir datos de uso de momeria a mb: `awk '{printf "%.1f", $1 / 1024}'`.

3. **Bucle de monitoreo**:  
   - Usa `while kill -0 $PID 2>/dev/null` para verificar si el proceso está activo.  
   - Registra logs con `date "+%Y-%m-%d %H:%M:%S"` para timestamps.  

4. **Cálculo de estadísticas**:  
   - Almacena valores de memoria en un array: `MEMORY_VALUES+=($mem)`.  
   - Usa `sort -nr` para máximo y `sort -n` para mínimo.  
   - Calcula promedio con `awk '{sum+=$1} END {print sum/NR}'`.  

5. **Manejo de errores**:  
   - Si no hay argumentos: `if [ $# -eq 0 ]; then...`.  
   - Si el proceso termina: `kill -0 $PID` retornará error.

6. **Calcular estadísticas de memoria**:
   ```bash
   # Calcular estadísticas
   MAX_MEM=$(printf "%s\n" "${MEMORY_VALUES[@]}" | sort -nr | head -1)
   MIN_MEM=$(printf "%s\n" "${MEMORY_VALUES[@]}" | sort -n | head -1)
   SUM=0
   COUNT=0

   # Recorrer los valores de memoria y sumarlos
   for VALUE in "${MEMORY_VALUES[@]}"; do
      SUM=$(echo "$SUM + $VALUE" | bc)
      COUNT=$((COUNT + 1))
   done

   # Manejar la división con bc para mayor precisión
   if [ "$COUNT" -gt 0 ]; then
      AVG_MEM=$(echo "scale=1; $SUM / $COUNT" | bc)
   else
      AVG_MEM=0
   fi
   ```

7. **Generar entradas para el reporte .md**
```bash
echo "# Reporte de Monitoreo - $PROCESS_NAME" > "$REPORT_FILE"
echo "## Fecha: $(date)" >> "$REPORT_FILE"
echo "## PID Monitoreado: $PID" >> "$REPORT_FILE"
echo "### Resumen:" >> "$REPORT_FILE"
echo "- **Tiempo Total de Monitoreo:** $TOTAL_TIME segundos" >> "$REPORT_FILE"
echo "- **Uso Máximo de Memoria:** ${MAX_MEM}MB" >> "$REPORT_FILE"
echo "- **Uso Mínimo de Memoria:** ${MIN_MEM}MB" >> "$REPORT_FILE"
echo "- **Uso Promedio de Memoria:** ${AVG_MEM}MB" >> "$REPORT_FILE"
echo "### Logs:" >> "$REPORT_FILE"
echo "\`\`\`" >> "$REPORT_FILE"
cat "$LOG_FILE" >> "$REPORT_FILE"
echo "\`\`\`" >> "$REPORT_FILE"

echo "Monitoreo finalizado. Reporte generado en: $REPORT_FILE"
```
---

## Instrucciones de Entrega  

1. **Crear un repositorio en GitHub**:  
   - Nombre: `lab1-[tu nombre]` (ej: `lab1-juan-perez`).  
   - Incluir los archivos: `monitor.sh`, `README.md`.  

2. **Configurar GitHub**:  
```bash
git init
git add .
git commit -m "Entrega Laboratorio 1"
git branch -M main
git remote add origin <URL de tu repositorio>
git push -u origin main
```

3. **Compartir el repositorio**:

Añadir al usuario `TheRadDani` como colaborador.

Enviar el enlace al correo del profesor antes de la fecha límite.

| Criterio                | Puntos |
|-------------------------|--------|
| Funcionalidad del script| 40%    |
| Claridad del reporte    | 30%    |
| Manejo de errores       | 20%    |
| Estructura del repositorio | 10% |

## Ejemplo de uso:
```
# Iniciar gedit (si no está en ejecución)
gedit &

# Ejecutar el script
./monitor.sh gedit

# Ver el reporte generado
cat /tmp/process_report.md
```


##  Notas Adicionales
Recursos:

Clases 1-3: Introducción a GNU/Linux, Text Manipulation, Process Management.

[Manual de Bash](https://www.gnu.org/software/bash/manual/bash.html)


¡Éxito!