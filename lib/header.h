#ifndef HEADER_H
#define HEADER_H
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <mlx.h>
#include <readline/readline.h>
#include <string.h>
// #include <cjson/cJSON.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct service_t
{
    int socket;
    int bind;
    int listen;
    struct sockaddr_in new_type_address;
    struct sockaddr old_type_address;
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