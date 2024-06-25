#include "header.h"
#include "physlib.h"
#include "server.h"

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
    service_t s;
    s.socket = socket(AF_INET, SOCK_STREAM, 0);
    if (s.socket < 0)
    {
        perror("Socket");
        exit(1);
    }
    s.server.sin_family = AF_INET;
    s.server.sin_port = htons(2020);
    s.server.sin_addr.s_addr = INADDR_ANY;
    int opt = 1;
    setsockopt(s.socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    s.bind = bind(s.socket, (const struct sockaddr*)&s.server, sizeof(s.server));
    if (s.bind < 0)
    {
        perror("Bind");
        exit(1);
    }

    s.listen = listen(s.socket, 5);
    if (s.listen < 0)
    {
        perror("Listen");
        exit(1);
    }

    while (1)
    {
        socklen_t len = sizeof(s.client);
        int client = accept(s.socket, (struct sockaddr*)&s.client, &len);
        if (client < 0)
            continue;
        else
        {
            int rt = read(client, s.request, sizeof(s.request));
            s.request[rt] = '\0';
            printf("%s\n", s.request);
            // headers_t *req = get_headers(s.request);
            // printf("%s\n", req->method);
        }
    }
}