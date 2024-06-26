#include "header.h"
#include "client.h"

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
    service_t *client = create_client(AF_INET, 2020, 0);    
    char *HTTP_request = 
        "%s %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: keep-alive\r\n"
        "\r\n"
        "{v0=%f,angle=%f}\n";

    free(client);
}