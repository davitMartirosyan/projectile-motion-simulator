#include "header.h"
#include "client.h"

int	main(int ac, char **av)
{
    if (ac < 3)
    {
        printf("Usage: <Port> <Ip> : 80 | 0.0.0.0\n");
        exit(1);
    }
    if (!ft_only_int(av[1]))
    {
        fprintf(stderr, "Port: Must be only and integer\n");
        exit(EXIT_FAILURE);
    }
    bomb_t bomb = {
        .velocity = 0.0,
        .angle = 0.0
    };
    service_t *client = create_client((uint16_t)ft_atoi(av[1]), av[2]);
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
                recv_packet(&ac, av, client, &bomb);
        }
		else
            printf("Enter Correct Values\n");
        free(angle);
        free(velocity);
    }
    free(client);

}


