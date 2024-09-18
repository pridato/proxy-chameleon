//
// Created by David Arroyo on 16/9/24.
//
#include "../include/proxy.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./../include/utils.h"

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

    server_addr.sin_family = AF_INET; // ipv4
    server_addr.sin_port = htons(8081); // de host -> red
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr); // convertimos la ip de text a binario

    // nos conectarnos a un socket ya creado del servidor
    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error al conectar al servidor");
        close(sock);
        exit(EXIT_FAILURE);
    }

    return sock;
}

/**
 * funcion para manejar el handhsake del websocket entre el proxy y el servidor
 * @param client_socket socket del cliente
 * @param server_socket socket del servidor final
 */
void handle_websocket_handshake(const int client_socket, const int server_socket) {
    char buffer[BUFFER_SIZE];

    ssize_t bytes_received = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_received <= 0) {
        perror("Error al leer del cliente");
        return;
    }

    send(server_socket, buffer, bytes_received, 0);

    bytes_received = read(server_socket, buffer, BUFFER_SIZE);
    if (bytes_received <= 0) {
        perror("Error al leer del servidor");
        return;
    }

    send(client_socket, buffer, bytes_received, 0);
}

/**
 * función para inicializar el proxy
 * @param listen_port
 * @param server_ip
 * @param server_port
 */
void start_proxy(const int listen_port, const char *server_ip, const int server_port) {
    struct sockaddr_in proxy_addr, client_addr;
    char buffer[BUFFER_SIZE] = {0};

    memset(&proxy_addr, 0, sizeof(proxy_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    const int proxy_socket = create_socket();

    // Configurar la dirección del proxy
    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_addr.s_addr = INADDR_ANY;
    proxy_addr.sin_port = htons(listen_port);

    // "bind" el socket al proxy dandole una ip
    if (bind(proxy_socket, (struct sockaddr *) &proxy_addr, sizeof(proxy_addr)) < 0) {
        perror("Error en bind");
        close(proxy_socket);
        exit(EXIT_FAILURE);
    }

    socklen_t client_addr_len = sizeof(client_addr);

    if (listen(proxy_socket, 3) < 0) {
        perror("Error en listen");
        exit(EXIT_FAILURE);
    }

    printf("Proxy escuchando en el puerto 8080...\n");

    while (1) {
        const int client_socket = accept(proxy_socket, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Error en accept");
            continue;
        }
        

        const int server_socket = connect_to_server(server_ip, server_port);

        handle_websocket_handshake(client_socket, server_socket);

        // Redirigir mensajes del cliente al servidor y viceversa
        while (1) {
            ssize_t bytes_received = read(client_socket, buffer, BUFFER_SIZE);
            if (bytes_received <= 0) break;
            send(server_socket, buffer, bytes_received, 0);

            bytes_received = read(server_socket, buffer, BUFFER_SIZE);
            if (bytes_received <= 0) break;
            send(client_socket, buffer, bytes_received, 0);
        }

        close(client_socket);
        close(server_socket);
    }
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
