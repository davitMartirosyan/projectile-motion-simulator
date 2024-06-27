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

    service_t *server = create_server(AF_INET, 2020, INADDR_ANY);
    // fcntl(server->socket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
    while (1)
    {
        socklen_t len = sizeof(server->client);
        int client = accept(server->socket, (struct sockaddr*)&server->client, &len);
            int rt = recv(client, server->request, sizeof(server->request) - 1, 0);
            if (rt < 0) {
                perror("Receive failed");
                break;
            } else if (rt == 0) {
                printf("Client disconnected\n");
                break;
            }
            server->request[rt] = '\0';
            printf("%s\n", server->request);
            memset(server->request, 0, sizeof(server->request));
    }
}