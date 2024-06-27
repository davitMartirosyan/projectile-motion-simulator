#ifndef HEADER_H
#define HEADER_H
#define _POSIX_C_SOURCE 199309L
#define _DARWIN_C_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>
#include "libft.h"
// #include <mlx.h>
// #include <cjson/cJSON.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct service_t
{
    int opt;
    int socket;
    union{
        int bind;
        int connect;
    };
    int listen;
    char request[4096];
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct sockaddr old_type_address;
    char ipv[255];
    struct in_addr ip;
} service_t;

typedef struct bomb_t
{
    float velocity;  // v m/s initial velocity
    double angle;
    // float vx0; // x >
    // float vy0; // y ^
    // float x;  // bomb x position
    // float y;  // bomb y position
} bomb_t;


#endif