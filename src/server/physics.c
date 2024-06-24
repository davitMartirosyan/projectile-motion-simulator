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