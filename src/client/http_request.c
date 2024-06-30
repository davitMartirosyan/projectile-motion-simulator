#include "header.h"
#include "server.h"

int send_packet(service_t *cli, bomb_t *bomb, char * method)
{
    // printf("%s\n", cli->ipv);
    char path[1024] = {0};
    char url_encode[1024] = {0};

    char *request = ft_strjoin("%s %s HTTP/1.1\r\n", NULL);
    request = ft_strjoin(request, "Host: %s\r\n");
    request = ft_strjoin(request, "Connection: keep-alive\r\n");
    request = ft_strjoin(request, "\r\n");
    if (strcmp(method, "POST") == 0)
    {
        sprintf(url_encode, "angle:%.3f:velocity:%.3f", bomb->angle, bomb->velocity);
        request = ft_strjoin(request, url_encode);
        request = ft_strjoin(request, "\n");
    }
    else if (strcmp(method, "GET") == 0)
        sprintf(path, "/phys?angle=%.3f&velocity=%.3f", bomb->angle, bomb->velocity);
    else
        return (0);
    sprintf(cli->request, request, method, !*path ? "/phys" : path, cli->ipv);
    ssize_t sd = send(cli->socket, cli->request, ft_strlen(cli->request), 0);
    if (sd < 0)
    {
        perror("send");
        return (0);
    }
    return (1);
}

int recv_packet(service_t *cli, bomb_t *bomb) {
    // int intervals = 0;
    // ssize_t rp = recv(cli->socket, &intervals, sizeof(int), 0);
    // if (rp < 0)
    // {
    //     perror("recv");
    //     return (0);
    // }
    // printf("N -> [%d]\n", intervals);
    // vec xyt[intervals];

    // memset(xyt, 0, sizeof(vec) * intervals);
    ssize_t rp = recv(cli->socket, cli->response, sizeof(cli->response), 0);
    if (rp < 0) {
        perror("recv");
        return 0;
    }
    // printf("%f : %f : [%f]\n", xyt[0].x, xyt[0].y, xyt[0].vy);
    return 1;
}