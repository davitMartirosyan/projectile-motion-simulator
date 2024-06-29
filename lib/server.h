#ifndef SERVER_H
#define SERVER_H
#include "header.h"

typedef struct headers_t
{
    char **headers;
    char **reqline;
    char *method;
    char *path;
    char *version;
}headers_t;

typedef struct set_t
{
    client_t clients[10];
    fd_set rset;
    fd_set wset;
}set_t;

typedef struct client_t
{
    headers_t *headers;
    char response[4096];
}client_t;


headers_t *get_headers(char *r);
service_t *create_server(int family, uint16_t port, uint32_t ipv);
headers_t *get_headers(char *r);

#endif