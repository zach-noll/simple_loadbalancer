#ifndef SERV_CLI_COMMUNICATION_H
#define SERV_CLI_COMMUNICATION_H

void *GetHTTP(int recv_servfd, int *end_sequence_pos, int num_of_end_sequence);

void SendHTTP(int sendfd, void *http_message, int msg_size);

void *CommunicateWithServer(int working_serverfd, void *http_request, int request_msg_size, int *response_msg_size);

#endif
