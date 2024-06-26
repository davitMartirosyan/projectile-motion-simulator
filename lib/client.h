#ifndef CLIENT_H
#define CLIENT_H
#include "header.h"

service_t *create_client(int family, uint16_t port, uint32_t ipv);

#endif