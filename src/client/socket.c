#include "client.h"

service_t *create_client(int family, uint16_t port, uint32_t ipv)
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
    service->client.sin_family = family;
    service->client.sin_port = htons(port);
    service->client.sin_addr.s_addr = htonl(ipv);

    service->connect = connect(service->socket, (const struct sockaddr*)&service->client, sizeof(service->client));
    if (service->connect < 0)
    {
        free(service);
        return (NULL);
    }
    return (service);
}