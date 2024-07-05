#ifndef CLIENT_H
#define CLIENT_H
#include "header.h"

service_t   *create_client(uint16_t port, char* ipv);
int         send_packet(service_t *cli, bomb_t *bomb, char * method);
// int         recv_packet(service_t *cli, bomb_t *bomb);
int         recv_packet(int *ac, char **av, service_t *cli, bomb_t *bomb);
#endif