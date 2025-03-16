# Generar un archivo de logs con 15 líneas que contienen "ERROR" y 5 líneas con "INFO"
echo "Generando archivo de logs de ejemplo..."
(
  for i in {1..15}; do 
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] ERROR: Problema en el servicio $i"
  done
  for i in {1..5}; do 
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] INFO: Tarea completada $i"
  done
) > access.log

echo "¡Archivo creado! Ejecuta el script con:"
echo "./process_logs.sh access.log ERROR"