#ifndef HEADER_H
#define HEADER_H
#define _DEFAULT_SOURCE
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
// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
//#include <GL/gl.h>
//#include <GL/glut.h>
#include "libft.h"
// #include <mlx.h>
// #include <cjson/cJSON.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct service_t
{
    int id;
    int opt;
    int socket;
    union{
        int bind;
        int connect;
    };
    int listen;
    char request[4096];
    char response[4096];
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct sockaddr old_type_address;
    char ipv[INET_ADDRSTRLEN];
    struct in_addr ip;
} service_t;

typedef struct bomb_t
{
    double velocity;
    double angle;
} bomb_t;

#endif
