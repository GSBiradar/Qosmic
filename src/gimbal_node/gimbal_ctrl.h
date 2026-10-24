/* Gimbal 1 kHz Position Loop + Ephemeris Interpolator */
#ifndef GIMBAL_CTRL_H
#define GIMBAL_CTRL_H

#include <stdint.h>

typedef struct {
    double t;
    double az, el;
    double vaz, vel; /* velocities */
    double aaz, ael;
} eph_point_t;

void interp_ephem(const eph_point_t *pts, int n, double t, double *paz,double *pel,double *vaz,double *vel,double *aaz,double *ael);
void pos_loop_1khz(double paz_ref,double pel_ref,double paz_fb,double pel_fb,double *uaz,double *uel);

#endif
