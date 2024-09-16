//
// Created by David Arroyo on 16/9/24.
//

#ifndef PROXY_H
#define PROXY_H

#define BUFFER_SIZE 4096

int connect_to_server(const char *server_ip, int server_port);
void start_proxy(int listen_port, const char *server_ip, int server_port);
int configure_proxy(int listen_port);
int create_socket();

#endif //PROXY_H
