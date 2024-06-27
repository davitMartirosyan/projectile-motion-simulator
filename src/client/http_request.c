#include "header.h"
#include "server.h"

int send_packet(service_t *cli, bomb_t *bomb, char * method)
{
    printf("%s\n", cli->ipv);
    char path[1024] = {0};
    char url_encode[1024] = {0};

    char *request = ft_strjoin("%s %s HTTP/1.1\r\n", NULL);
    request = ft_strjoin(request, "Host: %s\r\n");
    request = ft_strjoin(request, "Connection: keep-alive\r\n");
    request = ft_strjoin(request, "\r\n");
    if (strcmp(method, "POST") == 0)
    {
        sprintf(url_encode, "{angle:%.3f,velocity:%.3f}", bomb->angle, bomb->velocity);
        request = ft_strjoin(request, url_encode);
        request = ft_strjoin(request, "\n");
    }
    else if (strcmp(method, "GET") == 0)
        sprintf(path, "/phys?angle=%.3f&velocity=%.3f", bomb->angle, bomb->velocity);
    else
        return (0);
    // printf(request, method, !*path ? "/phys" : path, cli->ipv);
    sprintf(cli->request, request, method, !*path ? "/phys" : path, cli->ipv);
    ssize_t a = send(cli->socket, cli->request, ft_strlen(cli->request), 0);
    
    printf("%zu\n", a);
    return (1);
}

