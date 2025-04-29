# Universidad de Costa Rica
# Facultad de Ingeniería
# Escuela Ingeniería Eléctrica
# IE-0117 Programación Bajo Plataformas Abiertas

# Profesor: Ing. Luis Daniel Ferreto Chavarría

<div style="display: flex; justify-content: space-between; align-items: center;">
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="UCR Logo" style="width: 45%;"/>
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="EIE Logo" style="width: 45%;"/>
</div>

## Quiz 3: Manejo de Estructuras Encriptadas en C
## Objetivo
Leer un archivo encriptado que contiene una estructura `Sensor`, modificar su contenido añadiendo un campo `temperatura`, y guardarlo encriptado nuevamente.
## Temas: C
## Quiz Individual
## Fecha límite entrega 29-04-2025 12:00 pm CST

### Instrucciones del Quiz  


## Desarrolla un programa en C que:

* Lea un archivo encriptado (sensor_encrypted.bin) que contiene una estructura Sensor con los campos: id (int), valor (float), timestamp (char[20]).

* Imprima los valores de la estructura en pantalla.

* Añada un nuevo atributo temperatura (float) a la estructura.

* Asignar un valor numérico a este campo (ej: 30.0).

* Guarde la estructura actualizada encriptada en sensor_updated_encrypted.bin.

* Verifique el proceso leyendo el nuevo archivo y mostrando todos los campos (incluyendo temperatura).

## Entrega
- Repositorio GitHub con:
  - Código fuente del programa.
  - `README.md` explicativo.
  - Archivos encriptados generados (`sensor_encrypted.bin` y `sensor_updated_encrypted.bin`).
- Fecha límite: Hoy antes de medianoche.

## Funcion para encriptar archivos
```c
void encrypt_file(const char *input_filename, const char *output_filename, unsigned char key) {
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "wb");
    if (!input || !output) {
        perror("Error al abrir archivos");
        exit(1);
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        fputc(c ^ key, output);
    }

    fclose(input);
    fclose(output);
}
```

## Ejemplo de encriptar estructura en archivo
```c
int main() {
    Sensor sensor = {1, 25.5f, "2023-10-25 12:00:00"};
    
    // Guardar estructura en archivo temporal sin encriptar
    FILE *temp = fopen("temp.bin", "wb");
    fwrite(&sensor, sizeof(Sensor), 1, temp);
    fclose(temp);

    // Encriptar el archivo con XOR (clave 0xAB)
    encrypt_file("temp.bin", "sensor_encrypted.bin", 0xAB);
    remove("temp.bin"); // Eliminar temporal

    return 0;
}
```

## Notas
- Estructura original del `Sensor`:
  ```c
  typedef struct {
      int id;
      float valor;
      char timestamp[20];
  } Sensor;

## Restricciones:

* Trabajo individual.

* Usar GitHub para entrega (repositorio público con código, README.md y archivos encriptados).

* El archivo original se encriptó con XOR usando una clave de 1 byte (0xAB).


## Instrucciones de Entrega  

1. **Crear un repositorio en GitHub**:  
   - Nombre: `quiz2-[tu nombre]` (ej: `quiz2-juan-perez`).  
   - Incluir los archivos: `CMakeLists.txt`, `README.md`.
   - Mostrar captura del funcionamiento del programa target 

2. **Configurar GitHub**:  
```bash
cd ~
mkdir quiz2 && cd quiz3
git init
git add .
git commit -m "Entrega Laboratorio 1"
git branch -M main
git remote add origin <URL de tu repositorio>
git push -u origin main
```

3. **Compartir el repositorio**:

Añadir al usuario `TheRadDani` como colaborador.