#include "client.h"

service_t *create_client(int family, uint16_t port, char* ipv)
{
    service_t *service;
    service = (service_t*)malloc(sizeof(service_t));
    if (!service)
        return (NULL);
    memset(service, 0, sizeof(service_t));
    if (inet_aton(service->ipv, &service->ip) == 0)
    {
        perror("Inet-aton");
        free(service);
        return (NULL);
    }
    service->socket = socket(family, SOCK_STREAM, 0);
    if (service->socket < 0)
    {
        perror("Socket");
        free(service);
        return (NULL);
    }
    service->client.sin_family = family;
    service->client.sin_port = htons(port);
    service->client.sin_addr.s_addr = htonl(INADDR_ANY);
    service->connect = connect(service->socket, (const struct sockaddr*)&service->client, sizeof(service->client));
    if (service->connect < 0)
    {
        perror("Connect");
        free(service);
        return (NULL);
    }
    return (service);
}