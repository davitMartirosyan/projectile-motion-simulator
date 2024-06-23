#include "header.h"
#include "physlib.h"

void xy_data(double v0x, double v0y, double t, double g, int n, double dataArray[2])
{
    t = n * t;
    dataArray[0] = v0x * t;
    dataArray[1] = v0y * t - (0.5 * g * (t*t));  
}

double get_vx(double v, double angle)
{
    return (v * cos(angle * M_PI / 180));
}

double get_vy(double v, double angle)
{
    return (v * sin(angle * M_PI / 180));
}

double time_flight(double v0y, double g)
{
    return ((2 * v0y) / g);
}

double get_N_interval(double time_flight, double t)
{
    return (time_flight/t);
}