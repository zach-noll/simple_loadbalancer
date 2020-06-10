#ifndef SOCKET_TOOLS_H
#define SOCKET_TOOLS_H

#define TOTAL_SERVERS 3
#include <netdb.h>
#include <netinet/in.h>

int* AcceptServers(int server_socket);

int BindTry(char* filename, struct sockaddr_in service, int fd);

#endif
