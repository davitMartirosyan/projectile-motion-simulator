#ifndef CLIENT_H
#define CLIENT_H
#include "header.h"

service_t *create_client(int family, uint16_t port, char* ipv);
int send_packet(service_t *cli, bomb_t *bomb, char * method);

#endif