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
        int plex = select(max + 1, &rset_cp, &wset_cp, NULL, NULL);
        if (plex <= 0)
            continue;
        if (FD_ISSET(server->socket, &rset_cp))
        {
            //new connection
            socklen_t len = sizeof(server->client);
            int cli = accept(server->socket, (struct sockaddr*)&server->client, &len);
            if (cli < 0)
                continue;
            non_block(cli);
            FD_SET(cli, &set.rset);
            if (cli > max)
                max = cli;
            printf("new connection\n");
        }


        for(int fd = 2; fd <= max; fd++)
        {
            if (FD_ISSET(fd, &rset_cp) && fd != server->socket)
            {
                char buf[4096];
                ssize_t r = recv(fd, buf, sizeof(buf), 0);
                if (r <= 0)
                {
                    close(fd);
                    FD_CLR(fd, &set.rset);
                }
                buf[r] = '\0';
                printf("{{{{%d}}}}\n", fd);
                printf("%s", buf);
                ssize_t s = send(fd, buf, ft_strlen(buf), 0);
                if (s <= 0)
                {
                    close(fd);
                    FD_CLR(fd, &set.rset);
                }
            }
        }
    }   
}




/*

    {size:11,data: hello world}



*/