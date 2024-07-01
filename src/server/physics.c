#include "header.h"
#include "physlib.h"

double calc_vx(double v0, double angle)
{
    return (v0 * cos((angle * M_PI) / 180));
}

double calc_vy(double v0, double angle)
{
    return (v0 * sin((angle * M_PI) / 180));
}

double T_flight(double v0y, double g)
{
    return ((2 * v0y) / g);
}

double T_peak(double total_time)
{
    return (total_time / 2);
}

double H_max(double v0y, double g)
{
    return ((v0y * v0y) / (2 * g));
}

double R_range(double v0x, double total_time)
{
    return (v0x * total_time);
}

int N_interval(double total_time, double delta_time)
{
    return (round(total_time / delta_time));
}

double T_time(int n, double delta_time)
{
    return (n * delta_time);
}

double get_xt(double v0x, double t)
{
    return (v0x * t);
}

double get_yt(double v0y, double t, double g)
{
    return ((v0y * t) - (0.5 * g) * (t * t));
}

double get_vyt(double v0y, double g, double t)
{
    return (v0y - (g * t));
}

void calculate(int cli, bomb_t *bomb, double g)
{
	double vx = calc_vx(bomb->velocity, bomb->angle);
	double vy = calc_vy(bomb->velocity, bomb->angle);
	double total_time = T_flight(vy, g);
	double peak = T_peak(total_time);
	int interval = N_interval(total_time, 0.1);

	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = (1 % 10000) * 100000000;

    char buf[4096];
    memset(buf, 0, sizeof(buf));
    char *json = NULL;
    json = ft_strjoin(json, "HTTP/1.1 200 OK\r\n");
    json = ft_strjoin(json, "Content-Type: text/plain\r\n");
    // json = ft_strjoin(json, "Content-Length: 11\r\n");
    json = ft_strjoin(json, "\r\n");
    json = ft_strjoin(json, "{");
	for(int i = 0; i <= interval; i++)
	{
			// printf("{x: %f, y: %f} - [%f]\n",
            // get_xt(vx, T_time(i, 0.1)),
            // get_yt(vy, T_time(i, 0.1), g),
            // get_vyt(vy, g, T_time(i, 0.1))
			// 				);

            sprintf(buf, "{\"x\":%f,\"y\":%f,\"dt\":%f}",    get_xt(vx, T_time(i, 0.1)),
                                                get_yt(vy, T_time(i, 0.1), g),
                                                get_vyt(vy, g, T_time(i, 0.1)));
            json = ft_strjoin(json, buf);
			// nanosleep(&t, NULL);
	}
    json = ft_strjoin(json, "}");
    json = ft_strjoin(json, "\r\n");
    ssize_t sd = send(cli, json, ft_strlen(json), 0);
    free(json);
}