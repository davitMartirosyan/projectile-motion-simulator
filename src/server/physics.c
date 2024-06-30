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
    vec xy_pos_array[interval];
    memset(xy_pos_array, 0, sizeof(vec));
	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = (1 % 10000) * 100000000;

    printf("%d\n", interval);
    ssize_t s_interval = send(cli, &interval, sizeof(int), 0);
	for(int i = 0; i <= interval; i++)
	{
			printf("{x: %f, y: %f} - [%f]\n",
            get_xt(vx, T_time(i, 0.1)),
            get_yt(vy, T_time(i, 0.1), g),
            get_vyt(vy, g, T_time(i, 0.1))
							);
            // xy_pos_array[i].x =  get_xt(vx, T_time(i, 0.1));
            // xy_pos_array[i].y =  get_yt(vy, T_time(i, 0.1), 9.81);
            // xy_pos_array[i].vy = get_vyt(vy, 9.81, T_time(i, 0.1));
			nanosleep(&t, NULL);
	}

}