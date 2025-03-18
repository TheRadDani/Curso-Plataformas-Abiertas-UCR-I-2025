# Universidad de Costa Rica
# Facultad de Ingeniería
# Escuela Ingeniería Eléctrica
# IE-0117 Programación Bajo Plataformas Abiertas

# Profesor: Ing. Luis Daniel Ferreto Chavarría

<div style="display: flex; justify-content: space-between; align-items: center;">
  <img src="../images/ucr.png" alt="UCR Logo" style="width: 45%;"/>
  <img src="../images/eie.png" alt="EIE Logo" style="width: 45%;"/>
</div>

## Quiz 1: Script de Análisis de Logs
## Temas: Bash, Manipulación de Texto, Redirección

### Objetivo
Crear un script de Bash llamado analyze_logs.sh que procese un archivo de logs generado automáticamente y genere un informe con estadísticas específicas. No se permiten soluciones copiadas de internet o plagio; el ejercicio requiere decisiones creativas basadas en los conceptos de las clases.

## Requisitos
Entrada de argumentos:

El script debe aceptar dos argumentos:

$1: Ruta del archivo de logs (ejemplo: access.log).

$2: Palabra clave para filtrar registros (ejemplo: "ERROR").

## Funcionalidades:

* Si el archivo no existe, mostrar: "Error: El archivo $1 no existe. Use: $0 <archivo> <palabra>" y salir con código 1.

* Contar el número total de líneas en el archivo y guardarlo en una variable.

* Filtrar las líneas que contengan la palabra clave ($2) y guardarlas en resultados.txt.

* Contar cuántas veces aparece la palabra clave y mostrar: "Líneas analizadas: [total]. Coincidencias con '$2': [contador].".

* Si no hay coincidencias, crear un archivo errores.log con el mensaje: "$(date) - No se encontraron coincidencias para: $2".

## Manejo de errores y formato:

* Usar 2>/dev/null para ocultar errores de comandos internos.

* Asegurar que todas las variables estén entre comillas.

* Usar $0, $#, y $@ correctamente en los mensajes.

## Salida final:

* Si todo funciona, el script debe mostrar: "Informe generado en resultados.txt" y salir con código 0.

Ejemplo de uso:
```bash
bash analizar_logs.sh access.log ERROR  
Salida esperada en resultados.txt (si hay 3 coincidencias):
```

```bash
[Línea 5] ERROR: Usuario no encontrado  
[Línea 12] ERROR: Conexión fallida  
[Línea 19] ERROR: Permiso denegado  
```

## Validación
El script fallará si:

* No se proporcionan exactamente dos argumentos.

* El archivo de logs no existe.

* No tiene permisos de ejecución (recuerda usar chmod +x).

# Pistas:
* Usa `if [ $# -ne 2 ]` para verificar argumentos.

* Combina `grep -in` y redirección para guardar las líneas filtradas.

* Usa `wc -l` para contar líneas, pero considera cómo filtrar resultados.

* La fecha se puede obtener con `$(date '+%Y-%m-%d %H:%M:%S')`.

¡Entrega tu script y una captura de su ejecución exitosa!
Nota: Crea un archivo de prueba con echo -e "INFO: Inicio\nERROR: Fallo\nWARNING: Alerta" > test.log para validar tu solución
o utilizar el scrip `generate_log.sh` para generar un archivo `.log`.


## Instrucciones de Entrega  

1. **Crear un repositorio en GitHub**:  
   - Nombre: `quiz1-[tu nombre]` (ej: `quiz1-juan-perez`).  
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