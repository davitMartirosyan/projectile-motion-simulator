#include "header.h"
#include "client.h"

int	main(int ac, char **av)
{
    if (ac < 3)
    {
        printf("Usage: <Port> <Ip> : GET, POST | 80 | 0.0.0.0\n");
        exit(1);
    }
    bomb_t bomb = {
        .velocity = 0.0,
        .angle = 0.0
    };
    service_t *client = create_client(AF_INET, ft_atoi(av[2]), av[3]);
    if (!client)
        exit(1);
    while (1)
    {

        char *method = readline("Method: ");
        char *angle = readline("Angle: ");
        char *velocity = readline("Velocity: ");
        bomb.angle = strtod(angle, NULL);
        bomb.velocity = strtod(velocity, NULL);
        if (bomb.angle != 0 && bomb.velocity != 0)
		{
            if(send_packet(client, &bomb, method))
                recv_packet(client, &bomb);
        }
		else
            printf("Enter Correct Values\n");
        free(angle);
        free(velocity);
    }
    free(client);

}


