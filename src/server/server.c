#include "header.h"
#include "physlib.h"
#include "server.h"

char xy[10][10] = {
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}
};

double g = 0;

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Usage: -g Acceleration due to gravity\n");
        exit(1);
    }
    if (strcmp(av[1], "-g") != 0)
    {
        printf("Usage: -g Acceleration due to gravity\n");
        exit(1);
    }

    service_t *server = create_server(AF_INET, INADDR_ANY, 2020);
    while (1)
    {
        socklen_t len = sizeof(server->client);
        int client = accept(server->socket, (struct sockaddr*)&server->client, &len);
        if (client < 0)
            continue;
        else
        {
            int rt = read(client, server->request, sizeof(server->request));
            server->request[rt] = '\0';
            printf("%s\n", server->request);
        }
    }
}