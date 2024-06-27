#include "header.h"
#include "client.h"

int	main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Usage: <Request-method> <Port> <Ip> : GET, POST | 80 | 0.0.0.0\n");
        exit(1);
    }
    bomb_t bomb = {
        .velocity = 0,
        .angle = 0
    };
    service_t *client = create_client(AF_INET, 2020, av[3]);
    if (!client)
        exit(1);
    while (1)
    {
        char *angle = readline("Angle: ");
        char *velocity = readline("Velocity: ");
        bomb.angle = strtod(angle, NULL);
        bomb.velocity = strtod(velocity, NULL);
        if (bomb.angle != 0 && bomb.velocity != 0)
            send_packet(client, &bomb, av[1]);
        else
            printf("Enter Correct Values\n");
        free(angle);
        free(velocity);
    }
    free(client);
}