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
    if (!server)
        exit(1);
    
    fd_set rset;
    fd_set wset;
    FD_ZERO(&rset);
    FD_ZERO(&wset);

    FD_SET(server->socket, &rset);
    int max = server->socket;
    while (1)
    {
        fd_set rset_cp = rset;
        fd_set wset_cp = wset;
        int plexing = select(max + 1, &rset_cp, &wset_cp, NULL, NULL);
        if (plexing < 0)
        {
            perror("select");
            exit(1);
        }
        // if (FD_ISSET(server->socket, &rset_cp))
        // {
        //     socklen_t len = sizeof(server->client);
        //     int new_cli = accept(server->socket, (const struct sockaddr*)&server->client, &len);
        //     if (new_cli < 0)
        //         perror("connection refused");
        //     FD_SET(new_cli, &rset);
        //     max = (new_cli > max) ? new_cli : max;
        // }

        for(int fd = 0; fd <= max; fd++)
        {
            //new connection or client handling
            if(FD_ISSET(fd, &rset_cp))
            {
                if (fd == server->socket)
                {
                    //new client received
                }
                else if (fd != server->socket)
                {
                    
                    //client handling
                    
                }
            }
        }
    }
}