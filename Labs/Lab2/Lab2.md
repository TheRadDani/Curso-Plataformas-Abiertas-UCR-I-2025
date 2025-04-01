# Universidad de Costa Rica
# Facultad de Ingeniería
# Escuela Ingeniería Eléctrica
# IE-0117 Programación Bajo Plataformas Abiertas

# Profesor: Ing. Luis Daniel Ferreto Chavarría

<div style="display: flex; justify-content: space-between; align-items: center;">
  <img src="../images/ucr.png" alt="UCR Logo" style="width: 45%;"/>
  <img src="../images/eie.png" alt="EIE Logo" style="width: 45%;"/>
</div>

# Laboratorio 2: Redes de Computadoras
**Fecha de Entrega:** 13 de abril, 12:00 pm  
**Modalidad de Entrega:** Repositorio de GitHub (compartir enlace con el profesor)  
**Laboratorio individual**  
---

### Instrucciones del Laboratorio  

1. **Investigación teórica**:  
   - Definir los siguientes conceptos (máximo 3 líneas por cada uno):  
     - Dirección IP.  
     - DNS y su función principal.  
     - Redirección DNS (DNS hijacking).  
     - Protocolos TCP y UDP (diferencias clave).  

2. **Crear un script en Bash** (`check_dns.sh`) que realice lo siguiente:  
   - Comparar el servidor DNS configurado en el sistema con un servidor DNS confiable (ej: 8.8.8.8 de Google).  
   - Verificar si el dominio `example.com` resuelve a la misma IP en ambos servidores.  
   - Mostrar un mensaje indicando si hay discrepancia (posible redirección DNS).  
   - Usar comandos como `nslookup`, `dig` o `grep` para procesar la información.  

   **Ejemplo de estructura mínima:**  
   ```bash  
   #!/bin/bash  
   trusted_dns="8.8.8.8"  
   system_dns=$(grep "nameserver" /etc/resolv.conf | awk '{print $2}' | head -n 1)  
   ip_trusted=$(nslookup example.com $trusted_dns | grep "Address:" | tail -n 1 | awk '{print $2}')  
   ip_system=$(nslookup example.com $system_dns | grep "Address:" | tail -n 1 | awk '{print $2}')  

   if [ "$ip_trusted" != "$ip_system" ]; then  
       echo "¡Advertencia! Posible redirección DNS: $ip_system vs $ip_trusted"  
   else  
       echo "DNS coincide: $ip_system"  
   fi  
---

## Instrucciones de Entrega  

1. **Crear un repositorio en GitHub**:  
   - Nombre: `lab2-[tu nombre]` (ej: `lab2-juan-perez`).  
   - Incluir los archivos: `check_dns.sh`, `README.md`.  

2. **Configurar GitHub**:  
```bash
git init
git add .
git commit -m "Entrega Laboratorio 2"
git branch -M main
git remote add origin <URL de tu repositorio>
git push -u origin main
```

3. **Compartir el repositorio**:

Añadir al usuario `TheRadDani` como colaborador.

Enviar el enlace al correo del profesor antes de la fecha límite.

# Rúbrica de Evaluación - Lab 2: Fundamentos de Redes y Seguridad DNS  

| **Criterio**           | **Puntos** | **Descripción**                                                                 |
|-------------------------|------------|---------------------------------------------------------------------------------|
| **Funcionalidad del script** | 40%      | - El script compara correctamente las IPs de `example.com` entre DNS locales y confiables.<br>- Detecta y muestra claramente discrepancias (redirección DNS). |
| **Claridad del reporte** | 30%       | - Respuestas teóricas concisas y correctas.<br>- Explicación coherente de conceptos (IP, DNS, TCP/UDP, DNS hijacking). |
| **Manejo de errores**    | 20%       | - El script valida casos como DNS no accesibles, dominios inválidos o falta de herramientas.<br>- Mensajes de error útiles. |
| **Estructura del repositorio** | 10%    | - Archivos requeridos presentes (`check_dns.sh`, `README.md`).<br>- Captura de ejecución incluida.<br>- Repositorio compartido correctamente. |

## Ejemplo de uso:
```

# Ejecutar el script
bash check_dns.sh

```


# Recursos de Apoyo para el Laboratorio  

## 📚 Teoría de Redes y DNS  
1. **Introducción a Redes de Computadoras (Cisco Networking Basics)**  
   - [Enlace](https://www.cisco.com/c/en/us/solutions/small-business/resource-center/networking/networking-basics.html)  
   - Explica conceptos clave: IP, DNS, TCP/UDP.  

2. **Cómo funciona el DNS (Cloudflare)**  
   - [Enlace](https://www.cloudflare.com/es-es/learning/dns/what-is-dns/)  
   - Descripción clara del DNS y amenazas como el *DNS hijacking*.  

3. **Diferencias entre TCP y UDP (GeeksforGeeks)**  
   - [Enlace](https://www.geeksforgeeks.org/differences-between-tcp-and-udp/)  
   - Comparación técnica con ejemplos.  

## 💻 Comandos de Red en Linux  
4. **Tutorial de `nslookup` y `dig` (Linuxize)**  
   - [Enlace](https://linuxize.com/post/how-to-use-the-nslookup-command/)  
   - Uso práctico para resolver DNS y depurar.  

5. **Guía de `grep` y `awk` (Red Hat)**  
   - [Enlace](https://www.redhat.com/sysadmin/awk-grep-sed-oh-my)  
   - Procesamiento de texto para filtrar salidas de comandos.  

## 🛠 Scripting en Bash  
6. **Bash Scripting para Principiantes (FreeCodeCamp)**  
   - [Enlace](https://www.freecodecamp.org/news/bash-scripting-tutorial-linux-shell-script-and-command-line-for-beginners/)  
   - Sintaxis básica, variables y condicionales (`if-else`).  

7. **Manejo de Errores en Bash (Linux Handbook)**  
   - [Enlace](https://linuxhandbook.com/bash-error-handling/)  
   - Cómo validar entradas y manejar fallos.  

## 📦 Gestión de Repositorios en GitHub  
8. **Git y GitHub desde Cero (GitHub Docs)**  
   - [Enlace](https://docs.github.com/es/get-started/quickstart/hello-world)  
   - Configuración de repositorios y colaboración.  

## 🚨 Solución de Problemas Comunes  
9. **Problemas con `nslookup` en Diferentes SO (Stack Overflow)**  
   - [Enlace](https://stackoverflow.com/questions/3872339/nslookup-returns-wrong-ip-address)  
   - Cómo interpretar salidas inconsistentes.  

10. **Permisos de Ejecución en Linux (Tecmint)**  
    - [Enlace](https://www.tecmint.com/chmod-modify-file-directory-permissions/)  
    - Solucionar errores de `Permission denied` con `chmod +x`.  

## 🎥 Video Tutoriales (YouTube)  
11. **Scripting en Bash para Redes (En español)**  
    - [Enlace](https://www.youtube.com/watch?v=uI-xHPk4tO0)  
    - Ejemplos prácticos de automatización.  

12. **DNS Explicado en 5 Minutos (En inglés)**  
    - [Enlace](https://www.youtube.com/watch?v=mpQZVYPuDGU)  
    - Visualización rápida del flujo de DNS.  

¡Éxito!