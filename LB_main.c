#include "serv_cli_communication.h"
#include "socket_tools.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#define localhost "127.0.0.1"

int main()
{
  int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int http_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct sockaddr_in service;
  service.sin_family = AF_INET;
  service.sin_addr.s_addr = inet_addr(localhost);
  srand(time(0));

  server_socket = BindTry("server_port", service, server_socket);
  http_socket = BindTry("http_port", service, http_socket);

  if (listen(server_socket, TOTAL_SERVERS) != 0) {
    printf("listen to server failed\n");
  }

  if (listen(http_socket, TOTAL_SERVERS) != 0) {
    printf("listen to http failed\n");
  }

  int *serv_sock_arr = AcceptServers(server_socket);

  int working_serverfd = 0;
  int serv_num = 0;
  int recv_servfd;
  int request_msg_size;
  int response_size;
  void *http_request = NULL;
  void *http_response = NULL;

  while (1) {
    recv_servfd = accept(http_socket, NULL, NULL);

    http_request = GetHTTP(recv_servfd, &request_msg_size, 1);

    working_serverfd = serv_sock_arr[serv_num % TOTAL_SERVERS];

    http_response = CommunicateWithServer(working_serverfd, http_request, request_msg_size, &response_size);

    SendHTTP(recv_servfd, http_response, response_size);

    serv_num++;
  }
  free(http_request);
  free(http_response);
  free(serv_sock_arr);
  printf("done");
  return 0;
}
