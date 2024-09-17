//
// Created by David Arroyo on 16/9/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <sys/socket.h>
#include <arpa/inet.h>

#include "proxy.h"

int accept_client(int proxy_socket, struct sockaddr_in *client_addr, socklen_t *client_addr_len);
#endif //UTILS_H
