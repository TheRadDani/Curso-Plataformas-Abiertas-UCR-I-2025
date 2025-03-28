# Universidad de Costa Rica
# Facultad de Ingeniería
# Escuela Ingeniería Eléctrica
# IE-0117 Programación Bajo Plataformas Abiertas

# Profesor: Ing. Luis Daniel Ferreto Chavarría

<div style="display: flex; justify-content: space-between; align-items: center;">
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="UCR Logo" style="width: 45%;"/>
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="EIE Logo" style="width: 45%;"/>
</div>

## Quiz 2: Automatización en compilación de software
## Temas: C, CMake, Make

### Instrucciones del Quiz  

1. **Crear un archivo `CMakeLists.txt`** que cumpla con lo siguiente:  
   - Configurar versión mínima de CMake 3.10.  
   - Definir nombre del proyecto como **"Quiz2"** y versión **1.0**.  
   - Especificar el estándar de C como **C11**.  
   - Incluir los archivos de cabecera (.h) del directorio `include/`.  
   - Compilar los archivos fuente (.c) del directorio `src/`.  
   - Generar un ejecutable llamado **quiz2_app**.  
   - Usar variables de CMake (ej: `CMAKE_C_STANDARD`, `include_directories`, `add_executable`).  

   **Ejemplo de estructura mínima:**  
   ```cmake
   cmake_minimum_required(VERSION 3.10)  
   project(Quiz2 VERSION 1.0)  
   set(CMAKE_C_STANDARD 11)  
   include_directories(include)  
   add_executable(quiz2_app src/main.c src/funciones.c) 
```

## Instrucciones de Entrega  

1. **Crear un repositorio en GitHub**:  
   - Nombre: `quiz2-[tu nombre]` (ej: `quiz2-juan-perez`).  
   - Incluir los archivos: `CMakeLists.txt`, `README.md`.
   - Mostrar captura del funcionamiento del programa target 

2. **Configurar GitHub**:  
```bash
cd ~
mkdir quiz2 && cd quiz2
git init
git add .
git commit -m "Entrega Laboratorio 1"
git branch -M main
git remote add origin <URL de tu repositorio>
git push -u origin main
```

3. **Compartir el repositorio**:

Añadir al usuario `TheRadDani` como colaborador.