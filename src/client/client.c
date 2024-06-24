#include "header.h"

int	main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Usage: <Request-type>: GET, POST\n");
        exit(1);
    }

    bomb_t bomb = {
        .velocity = 25,
        .angle = 45,
    };

    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    struct hostent *server;
    char buf[4096];
    if (s < 0)
    {
        perror("Socket");
        exit(1);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    int con = connect(s, (const struct sockaddr*)&addr, sizeof(addr));
    if (con < 0)
    {
        perror("Connect");
        close(s);
        exit(1);
    }

    char *req_path = "/?v0=%f;angle=%f";
    char req_buf[4096];
    sprintf(req_buf, req_path, (double)25, (double)45);
    
    char *HTTP_request = 
        "%s %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: keep-alive\r\n\r\n"
        "\r\n"
        "{v0=%f,angle=%f}";

    sprintf(buf, HTTP_request, 
        av[1], req_buf,
        "127.0.0.1",
        sizeof(bomb_t));
    send(s, buf, strlen(buf), 0);
}
