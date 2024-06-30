#include "client.h"

service_t *create_client(uint16_t port, char* ipv)
{
    service_t *service;
    service = (service_t*)malloc(sizeof(service_t));
    if (!service)
        return (NULL);
    memset(service, 0, sizeof(service_t));
    // strcpy(service->ipv, ipv);
    if (inet_pton(AF_INET, ipv, (struct in_addr*)&service->ip) != 1)
    {
        fprintf(stderr, "Invalid Ip address format\n");
        free(service);
        return (NULL);
    }
    service->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (service->socket < 0)
    {
        perror("Socket");
        free(service);
        return (NULL);
    }
    service->client.sin_family = AF_INET;
    service->client.sin_port = htons(port);
    service->client.sin_addr.s_addr = service->ip.s_addr;
    service->connect = connect(service->socket, (const struct sockaddr*)&service->client, sizeof(service->client));
    if (service->connect < 0)
    {
        perror("Connect");
        free(service);
        return (NULL);
    }
    return (service);
}