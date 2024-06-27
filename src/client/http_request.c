#include "header.h"
#include "server.h"

int send_packet(service_t *cli, bomb_t *bomb, char * method)
{
    char json_path[1024] = {"/phys"};

    char *request = ft_strjoin("%s %s HTTP/1.1\r\n", NULL);
    request = ft_strjoin(request, "Host: %s\r\n");
    request = ft_strjoin(request, "Connection: keep-alive\r\n");
    request = ft_strjoin(request, "\r\n");
    if (strcmp(method, "POST") == 0)
    {
        sprintf(json_path, "{angle:%.3f,velocity:%.3f}", bomb->angle, bomb->velocity);
        request = ft_strjoin(request, json_path);
    }
    else if (strcmp(method, "GET") == 0)
        sprintf(json_path, "/phys?angle=%.3f&velocity=%.3f", bomb->angle, bomb->velocity);

    printf(request, method, json_path, cli->ipv);
    return (0);
}

