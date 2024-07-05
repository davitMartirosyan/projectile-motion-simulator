#include "header.h"
#include "physlib.h"
#include "server.h"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        printf("Usage: <Port> <Ip>\n");
        exit (EXIT_FAILURE);
    }
    service_t *server = create_server(AF_INET, (uint16_t)ft_atoi(av[1]), av[2]);
    set_t set = {0};
    bomb_t bomb = {0};

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
                    continue;
                }
                buf[r] = '\0';
                headers_t *req = get_headers(buf);
                if (req)
                {
                    if (strcmp(req->reqline[0], "GET") == 0)
                    {
                        printf("GET: %s\n", req->reqline[1]);
                    }
                    else if (strcmp(req->reqline[0], "POST") == 0)
                    {
                        int size = 0;
                        char **body = ft_split_sized(req->headers[req->size - 1], ':', &size);
                        if (body)
                        {
                            bomb.angle = strtod(body[1], NULL);
                            bomb.velocity = strtod(body[3], NULL);
                            printf("%f : %f\n", bomb.angle, bomb.velocity);
                            for(int i = 0; i < size; i++)
                                free(body[i]);
                            free(body);
                        }
                    }
                    calculate(fd, &bomb, 9.81);
                }
            }
        }
    }   
}




/*

    {size:11,data: hello world}



*/