
#include "socket_tools.h"
#include <stdio.h>
#include <stdlib.h>
#define MIN_PORT 1024
#define MAX_PORT 64000

#define SA struct sockaddr

void WritePortToFile(char *filename, int port)
{
  FILE *fp;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("unable to open %s file\n", filename);
    return;
  }
  fprintf(fp, "%d", port);
  fclose(fp);
}

int GenerateRandPort() { return rand() % (MAX_PORT - MIN_PORT) + MIN_PORT; }

int *AcceptServers(int server_socket)
{
  unsigned i;
  int *servers_fd = malloc(sizeof(int) * TOTAL_SERVERS);
  for (i = 0; i < TOTAL_SERVERS; i++) {
    servers_fd[i] = accept(server_socket, NULL, NULL);
  }
  return servers_fd;
}

void ListenSocket(int server_socket, int http_socket)
{
  if (listen(server_socket, TOTAL_SERVERS) != 0) {
    printf("listen to server failed\n");
  }

  if (listen(http_socket, TOTAL_SERVERS) != 0) {
    printf("listen to http failed\n");
  }

  return;
}

int BindTry(char *filename, struct sockaddr_in service, int fd)
{
  while (1) {
    int port = GenerateRandPort();
    service.sin_port = htons(port);
    if (bind(fd, (SA *)&service, sizeof(service)) == 0) {
      WritePortToFile(filename, port);
      return fd;
    }
  }
}
