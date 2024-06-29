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
                    // printf("neww\n");
                    socklen_t len = sizeof(server->client);
                    int cli = accept(server->socket, (const struct sockaddr*)&server->client, &len);
                    // printf("accept\n");
                    if (cli < 0) continue;
                    set.clients[cli].fd = cli;
                    max = (cli > max) ? cli : max;
                    FD_SET(cli, &set.rset);
                }
                else
                {
                    //client handling
                    // ssize_t rd = recv(fd, set.clients[fd].response, sizeof(set.clients[fd].response), 0);
                    // set.clients[fd].request[rd] = '\0';
                    // printf("%s", set.clients[fd].response);
                    // memset(set.clients[fd].request, 0, sizeof(set.clients[fd].request));

                    char buf[4096] = {0};
                    ssize_t rd = recv(fd, buf, sizeof(buf), 0);
                    buf[rd] = '\0';
                    char html[4096] = 
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "\r\n"
                        "<html>"
                        "<body"
                        "<h1>"
                        "hello world"
                        "</h1>"
                        "</body>"
                        "</html>";
                    int a = send(fd, html, ft_strlen(html), 0);
                    printf("send: %d\n", a);
                    close(fd);
                    FD_CLR(fd, &rset_cp);
                    FD_CLR(fd, &set.rset);
                }
            }
        }

        // for(int fd = 2; fd <= max; fd++)
        // {
        //     if(FD_ISSET(fd, &wset_cp))
        //     {
        //         char buf[1024] = {0};
        //         ssize_t sd = send(fd, buf, sizeof(buf), 0);
        //     }
        // }
    }
}




/*

    {size:11,data: hello world}



*/