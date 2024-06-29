#include "header.h"
#include "physlib.h"
#include "server.h"

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
    set_t set = {0};
    if (!server)
        exit(1);

    FD_ZERO(&set.rset);
    FD_ZERO(&set.wset);
    FD_SET(server->socket, &set.rset);

    int max = server->socket;
    while (1)
    {
        fd_set rset_cp = set.rset;
        fd_set wset_cp = set.wset;
        int plexing = select(max + 1, &rset_cp, &wset_cp, NULL, NULL);
        if (plexing < 0)
        {
            perror("select");
            exit(1);
        }
        for(int fd = 0; fd <= max; fd++)
        {
            if (FD_ISSET(fd, &rset_cp))
            {
                if (fd == server->socket)
                {
                    //new connection
                    socklen_t len = sizoef(server->client);
                    int cli = accept(server->socket, (const struct sockaddr*)&server->client, &len);
                    if (cli < 0) continue;
                    FD_SET(cli, &set.rset);
                    set.clients[server->id++];
                }
                else
                {
                    //client handling

                }
            }
        }

    }
}




/*

    {size:11,data: hello world}



*/