#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_LEN 1024

int CheckForEnd(char *buff, int size_of_buff, int end_of_line_count)
{
  char end_str[] = "\r\n\r\n";
  int counter = 0;
  size_t n = strlen(end_str);
  unsigned cur_pos = 0;
  while (cur_pos <= size_of_buff - n) {
    if (memcmp(buff + cur_pos, end_str, n) == 0) {
      counter++;
      if (counter == end_of_line_count) {
        return cur_pos + n;
      }
    }
    cur_pos++;
  }
  return 0;
}

void *GetHTTP(int recv_servfd, int *end_sequence_pos, int num_of_end_sequence)
{
  int count = 0;
  int cur_size = 0;
  void *http_response = NULL;
  while (1) {
    if (count >= cur_size) {
      cur_size += BUFF_LEN;
      http_response = realloc(http_response, cur_size);
    }
    count += recv(recv_servfd, http_response + count, BUFF_LEN, 0);
    if (count == 0) {
      printf("something went wrong\n");
    }

    *end_sequence_pos = CheckForEnd(http_response, cur_size, num_of_end_sequence);

    if (*end_sequence_pos > 0) {
      return http_response;
    } else {
      continue;
    }
  }
}
void SendHTTP(int sendfd, void *http_message, int msg_size)
{
  int bytes_written = 0;

  while (bytes_written < msg_size) {
    bytes_written += write(sendfd, http_message, msg_size);
  }

  return;
}

void *CommunicateWithServer(int working_serverfd, void *http_request, int request_msg_size, int *response_msg_size)
{

  SendHTTP(working_serverfd, http_request, request_msg_size);
  void *http_response = GetHTTP(working_serverfd, response_msg_size, 2);
  return http_response;
}
