# Universidad de Costa Rica
# Facultad de Ingeniería
# Escuela Ingeniería Eléctrica
# IE-0117 Programación Bajo Plataformas Abiertas

# Profesor: Ing. Luis Daniel Ferreto Chavarría

<div style="display: flex; justify-content: space-between; align-items: center;">
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="UCR Logo" style="width: 45%;"/>
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="EIE Logo" style="width: 45%;"/>
</div>

## Quiz 4: Refactorización de Código y Configuración de CMake

## Temas: C
## Quiz Individual
## Fecha límite entrega 06-05-2025 5:00 pm CST

### Instrucciones del Quiz  

1. Estudiar el código dado:

* En la Class12, se encuentra la carpeta src con el código fuente del archivo example1.c. Este código implementa una red neuronal para resolver el problema XOR.

2. Refactorizar el código:

* Crear encabezados (headers):

    * Extraer las declaraciones de funciones y estructuras (como NeuralNetwork, create_neural_network, forward_propagate, etc.) del código.

    * Crear un archivo library.h dentro de la carpeta include para alojar estos encabezados.

* Implementar funciones en archivos fuente:

    * Mover las implementaciones de las funciones a un nuevo archivo en la carpeta src (ej. library.c).

* Simplificar main.c:

    * Dejar en main.c solo la función main y el código que llama a las funciones (como se muestra en el código proporcionado).

    * Asegurarse de incluir library.h en main.c para acceder a las funciones.

3. Estructura de carpetas requerida:
```bash
proyecto/  
├── include/  
│   └── library.h  
├── src/  
│   ├── library.c  
│   └── main.c  
└── build/  
```

4. Crear CMakeLists.txt:

* Configurar un CMakeLists.txt que:

    * Compile el proyecto como un ejecutable.

    * Inclua la carpeta include para los encabezados.

    * Genere el ejecutable en la carpeta build.

5. Compilación:

* Ejecutar los siguientes comandos desde la raíz del proyecto:

```bash
mkdir -p build  
cd build  
cmake ..  
make  
```


## Entregables:

* Carpeta include con library.h.

* Carpeta src con library.c y main.c (este último solo con la función main).

* Archivo CMakeLists.txt funcional.

* El código debe compilar sin errores y ejecutar el entrenamiento/prueba de la red neuronal como en el código original.

## Notas:

* Asegúrate de que las funciones como create_neural_network, forward_propagate, backward_propagate, predict, save_neural_network, y load_neural_network estén correctamente declaradas en library.h e implementadas en library.c.

* Usa include guards en library.h.

* Verifica que no haya código de implementación de funciones en main.c.

## Instrucciones de Entrega  

1. **Crear un repositorio en GitHub**:  
   - Nombre: `quiz4-[tu nombre]` (ej: `quiz4-juan-perez`).  
   - Mostrar captura del funcionamiento del programa target 

2. **Configurar GitHub**:  
```bash
cd ~
mkdir quiz4 && cd quiz4
git init
git add .
git commit -m "Entrega Quiz 4"
git branch -M main
git remote add origin <URL de tu repositorio>
git push -u origin main
```

3. **Compartir el repositorio**:

Añadir al usuario `TheRadDani` como colaborador.