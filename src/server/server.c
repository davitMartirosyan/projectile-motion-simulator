#include "header.h"
#include "physlib.h"

int main(int ac, char **av)
{
    double vx = calc_vx(25, 45);
    double vy = calc_vy(25, 45);
    double total_time = T_flight(vy, 9.81);
    double peak = T_peak(total_time);
    double interval = N_interval(total_time, 0.1);

    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = (1 % 10000) * 100000000;

    for(int i = 0; i < interval; i++)
    {
        printf("{x: %f, y: %f} - [%f]\n", get_xt(vx, T_time(i, 0.1)), get_yt(vy, T_time(i, 0.1), 9.81), get_vyt(vy, 9.81, T_time(i, 0.1)));
        nanosleep(&t, NULL);
    }

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