#ifndef SERVER_H
#define SERVER_H
#include "header.h"

typedef struct map
{
    char *key;
    char *value;
    struct map* next;
} map;

typedef struct headers_t
{
    char **headers;
    char **reqline;
    char *method;
    char *path;
    char *version;

}headers_t;

headers_t *get_headers(char *r);
service_t *create_server(int family, uint16_t port, uint32_t ipv);
headers_t *get_headers(char *r);

#endif