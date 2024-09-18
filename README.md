# Proyecto de Proxy con Compresión y Servidor WebSocket

Este proyecto consiste en un proxy en C que maneja la comunicación entre un cliente WebSocket y un servidor WebSocket. Los mensajes enviados a través del proxy están comprimidos para mejorar la velocidad y eficiencia de la comunicación. El cliente y el servidor están implementados en Python utilizando la biblioteca `websockets`.

## Estructura del Proyecto

- **proxy.c**: Implementación del proxy en C que recibe conexiones de clientes, maneja la compresión y descompresión de datos, y los reenvía al servidor WebSocket.
- **proxy.h**: Archivo de encabezado para las funciones del proxy.
- **utils.h**: Funciones utilitarias utilizadas por el proxy.
- **client.py**: Cliente WebSocket en Python que se conecta al proxy, envía un mensaje, y recibe una respuesta.
- **server.py**: Servidor WebSocket en Python que recibe mensajes del proxy, responde con un eco, y envía los mensajes comprimidos.

## Requisitos

- **C**: Se requiere un compilador de C como `gcc`.
- **Python**: Se requiere Python 3.7 o superior.
- **Bibliotecas de Python**:
  - `websockets`
  - `zlib` (incluida en la biblioteca estándar de Python)

## Instalación

### Configuración del Proxy en C

1. **Compila el código del proxy**:

   ```bash
   gcc -o proxy proxy.c -lz
    ```

2. **Ejecuta el proxy**:

   ```bash
   ./proxy
    ```

*Descripción del Funcionamiento*
1. Proxy en C:

  Escucha en el puerto 8080 para conexiones entrantes de clientes WebSocket.
  Se conecta al servidor WebSocket en el puerto 8081.
  Maneja el "handshake" del WebSocket y redirige mensajes entre el cliente y el servidor.
  Los mensajes son comprimidos antes de enviarse al servidor y descomprimidos antes de enviarse al cliente.
  Servidor WebSocket en Python:

2. Servidor WebSocket en Python:

  Escucha en el puerto 8081.
  Recibe mensajes del proxy, los descomprime, y envía una respuesta de eco.
  Los mensajes de respuesta son comprimidos antes de ser enviados al proxy.
  Cliente WebSocket en Python:

3. Cliente WebSocket en Python:
Se conecta al proxy en el puerto 8080.
Envía un mensaje al servidor a través del proxy.
Recibe la respuesta del servidor a través del proxy y la muestra en la consola.

