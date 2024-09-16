//
// Created by David Arroyo on 16/9/24.
//
#include "../include/proxy.h"
#include "../include/constants.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Función para conectarse al servidor final
 * @param server_ip ip del servidor a conectar
 * @param server_port su ip
 * @return el propio socketweb conectado
 */
int connect_to_server(const char *server_ip, int server_port) {
    const int sock = create_socket();

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    // configuración del servidor
    server_addr.sin_family = AF_INET; // ipv4
    server_addr.sin_port = htons(server_port); // de host -> red
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr); // convertimos la ip de text a binario

    // nos conectarnos a un socket ya creado del servidor
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr) < 0)) {
        perror("Error al conectar al servidor");
        close(sock);
        exit(EXIT_FAILURE);
    }

    return sock;
}

/**
 * función para inicializar el proxy
 * @param listen_port
 * @param server_ip
 * @param server_port
 */
void start_proxy(const int listen_port, const char *server_ip, int server_port) {
    int client_socket, server_socket;
    char buffer[BUFFER_SIZE] = {0};

    const int proxy = configure_proxy(listen_port);

    // Escuchar conexiones entrantes max 3 clientes colas
    if (listen(proxy, 3) < 0) {
        perror("Error en listen");
        exit(EXIT_FAILURE);
    }

    printf("Proxy escuchando en el puerto 8080...\n");

}

/**
 * configurar proxy y vincularlo al socket
 * @param listen_port puerto en el que está corriendo el servidor
 * @return el proxy "binded" con socket
 */
int configure_proxy(int listen_port) {
    struct sockaddr_in proxy_addr, client_addr;
    memset(&proxy_addr, 0, sizeof(proxy_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    const int proxy_socket = create_socket();

    // Configurar la dirección del proxy
    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_addr.s_addr = INADDR_ANY;
    proxy_addr.sin_port = htons(listen_port);

    // "bind" el socket al proxy dandole una ip
    if (bind(proxy_socket, (struct sockaddr *)&proxy_addr, sizeof(proxy_addr)) < 0) {
        perror("Error en bind");
        close(proxy_socket);
        exit(EXIT_FAILURE);
    }

    return proxy_socket;
}

/**
 * Función para crear un socket ipv4, con TCP sin ningún flag
 * @return int del socket generado
 */
int create_socket() {
    const int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error al crear el websocket");
        exit(EXIT_FAILURE);
    }

    return sock;
}