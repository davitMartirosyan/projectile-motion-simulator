#include "header.h"
#include "server.h"

int send_packet(service_t *cli, bomb_t *bomb, char * method)
{
    char path[1024] = {0};
    char url_encode[1024] = {0};
    char *request = ft_strjoin("%s %s HTTP/1.1\r\n", NULL);
    request = ft_strjoin(request, "Host: %s\r\n");
    request = ft_strjoin(request, "Connection: keep-alive\r\n");
    request = ft_strjoin(request, "\r\n");
    if (strcmp(method, "POST") == 0)
    {
        sprintf(url_encode, "angle:%.3f:velocity:%.3f", bomb->angle, bomb->velocity);
        request = ft_strjoin(request, url_encode);
        request = ft_strjoin(request, "\n");
    }
    else if (strcmp(method, "GET") == 0)
        sprintf(path, "/phys?angle=%.3f&velocity=%.3f", bomb->angle, bomb->velocity);
    else
        return (0);
    sprintf(cli->request, request, method, !*path ? "/phys" : path, cli->ipv);
    ssize_t sd = send(cli->socket, cli->request, ft_strlen(cli->request), 0);
    if (sd < 0)
    {
        perror("send");
        return (0);
    }
    return (1);
}

int recv_packet(int *ac, char **av, service_t *cli, bomb_t *bomb) {
    int intervals = 0;
    ssize_t receive_interval = recv(cli->socket, &intervals, sizeof(int), 0);
    if (receive_interval < 0)
    {
        perror("recv");
        return (0);
    }
    printf("N -> [%d]\n", intervals);
    vec xyt[intervals + 1];
    ssize_t receive_data = recv(cli->socket, xyt, (sizeof(vec) * (intervals+1)), 0);
    if (receive_data < 0) {
        perror("recv");
        return 0;
    }
    struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = (1 % 10000) * 100000000;

    // for(int i = 0; i <= intervals; i++)
    // {
    //     printf("%d : %f : %f : %f\n", i, xyt[i].x, xyt[i].y, xyt[i].vy);
    //     // nanosleep(&t, NULL);
    // }
    #define SIZE 10
    char grid[SIZE][SIZE];
    
    // Initialize the grid with spaces
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = ' ';
        }
    }

    // Find the maximum x and y to scale coordinates
    double max_x = 0, max_y = 0;
    for (int i = 0; i < 36; i++) {
        if (xyt[i].x > max_x) max_x = xyt[i].x;
        if (xyt[i].y > max_y) max_y = xyt[i].y;
    }

    // Plot the trajectory
    for (int i = 0; i < 36; i++) {
        int scaled_x = (int)((xyt[i].x * (SIZE - 1)) / max_x);
        int scaled_y = (int)((xyt[i].y * (SIZE - 1)) / max_y);
        
        // Ensure the points are within bounds
        if (scaled_x >= SIZE) scaled_x = SIZE - 1;
        if (scaled_y >= SIZE) scaled_y = SIZE - 1;

        grid[scaled_y][scaled_x] = '*';
    }

    // Print the grid
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    return 1;
}