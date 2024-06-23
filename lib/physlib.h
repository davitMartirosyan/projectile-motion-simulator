#ifndef PHYSLIB_H
#define PHYSLIB_H

void    xy_data(double v0x, double v0y, double t, double g, int n, double dataArray[2]);
double  get_vx(double v, double angle);
double  get_vy(double v, double angle);
double  time_flight(double v0y, double g);
double  get_N_interval(double time_flight, double t);

#endif