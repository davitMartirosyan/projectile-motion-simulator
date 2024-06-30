#include "server.h"

void non_block(int socket)
{
    int fl = fcntl(socket, F_GETFL, 0);
    if (fl == -1)
    {
        perror("F_GETFL");
        exit(1);
    }
    if (fcntl(socket, F_SETFL, fl | O_NONBLOCK) == -1)
    {
        perror("O_NONBLOCK");
        exit(1);
    }
}

service_t *
create_server(int family, uint16_t port, uint32_t ipv)
{
    service_t *service;

    service = (service_t*)malloc(sizeof(service_t));
    if (!service)
        return (NULL);
    memset(service, 0, sizeof(service_t));
    service->socket = socket(family, SOCK_STREAM, 0);
    if (service->socket < 0)
    {
        free(service);
        return (NULL);
    }
    service->opt = 1;
    service->server.sin_family = family;
    service->server.sin_port = htons(port);
    service->server.sin_addr.s_addr = htonl(ipv);
    setsockopt(service->socket, SOL_SOCKET, SO_REUSEADDR, &service->opt, sizeof(service->opt));
    service->bind = bind(service->socket, (const struct sockaddr*)&service->server, sizeof(service->server));
    non_block(service->socket);
    if (service->bind < 0)
    {
        free(service);
        return (NULL);
    }
    service->listen = listen(service->socket, 5);
    if (service->listen < 0)
    {
        free(service);
        return (NULL);
    }
    return (service);
}