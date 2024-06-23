#include "header.h"
#include "physlib.h"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Usage: -g Acceleration due to gravity\n");
        exit(1);
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Socket");
        exit(1);
    }
    struct sockaddr_in addr;
    struct sockaddr_in cl;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    int b = bind(sock, (const struct sockaddr*)&addr, sizeof(addr));
    if (b < 0)
    {
        perror("Bind");
        exit(1);
    }
    int l = listen(sock, 5);
    if (l < 0)
    {
        perror("Listen");
        exit(1);
    }
    while (1)
    {
        socklen_t len = sizeof(cl);
        int client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0)
            continue;
        else
        {
            char buf[1024];
            int r = recv(client, buf, sizeof(buf), 0);
            buf[r] = '\0';
            printf("%s\n", buf);
        }
    }
}