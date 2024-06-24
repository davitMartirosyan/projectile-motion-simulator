#ifndef PHYSLIB_H
#define PHYSLIB_H


double  calc_vx(double v0, double angle);
double  calc_vy(double v0, double angle);
double  get_xt(double v0x, double t);
double  get_yt(double v0y, double t, double g);
double  get_vyt(double v0y, double g, double t);
double  T_flight(double v0y, double g);
double  T_peak(double total_time);
double  H_max(double v0y, double g);
double  R_range(double v0x, double total_time);
double  T_time(int n, double delta_time);
int     N_interval(double total_time, double delta_time);


#endif