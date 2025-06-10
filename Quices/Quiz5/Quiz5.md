# Universidad de Costa Rica
# Facultad de Ingeniería
# Escuela Ingeniería Eléctrica
# IE-0117 Programación Bajo Plataformas Abiertas

# Profesor: Ing. Luis Daniel Ferreto Chavarría

<div style="display: flex; justify-content: space-between; align-items: center;">
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="UCR Logo" style="width: 45%;"/>
  <img src="/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/images" alt="EIE Logo" style="width: 45%;"/>
</div>

## Quiz 5: Servidor TCP y Comunicación de Red

Instrucciones:
Sigue los pasos a continuación para completar el quiz. Debes compilar, ejecutar e interactuar con un servidor TCP que te enviará las preguntas del quiz en formato Markdown.

Pasos a realizar:

1. Compila el siguiente código C++
Guarda el código en un archivo (ej. server.cpp) y compílalo con g++:

```bash
g++ server.cpp -o server -std=c++11
```

2. Ejecuta el servidor
Inicia el programa en un terminal. Escuchará en el puerto `7000`:

```bash
./server
```

3. Conéctate al servidor usando Netcat (nc)
En otro terminal

# Notas:
El servidor se cerrará automáticamente después de enviar el quiz.

Si tienes errores de compilación, verifica que tengas instalado g++ y las librerías de desarrollo de red.