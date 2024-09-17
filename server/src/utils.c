//
// Created by David Arroyo on 16/9/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "./../include/utils.h"

#include "../include/proxy.h"

/**
 * Acepta una conexión de cliente al socket del servidor
 *
 * @param proxy_socket Socket del proxy que está escuchando conexiones.
 * @param client_addr Dirección del cliente que está intentando conectarse.
 * @param client_addr_len Longitud de la dirección del cliente.
 * @return El socket de cliente si la conexión es aceptada con éxito.
 */
int accept_client(const int proxy_socket, struct sockaddr_in *client_addr, socklen_t *client_addr_len) {
    const int client_socket = accept(proxy_socket, (struct sockaddr *) client_addr, client_addr_len);
    if (client_socket < 0) {
        perror("Error en accept");
        close(proxy_socket);
        exit(EXIT_FAILURE);
    }
    return client_socket;
}
