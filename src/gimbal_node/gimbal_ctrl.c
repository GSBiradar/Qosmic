#include "gimbal_ctrl.h"
#include <math.h>

void interp_ephem(const eph_point_t *pts, int n, double t, double *paz,double *pel,double *vaz,double *vel,double *aaz,double *ael)
{
    /* Lagrange/interp between points, compute vel/accel via finite diff or spline */
    (void)pts; (void)n; (void)t;
    if(paz)*paz=0;if(pel)*pel=0;if(vaz)*vaz=0;if(vel)*vel=0;if(aaz)*aaz=0;if(ael)*ael=0;
}

void pos_loop_1khz(double paz_ref,double pel_ref,double paz_fb,double pel_fb,double *uaz,double *uel)
{
    double eaz = paz_ref - paz_fb;
    double eel = pel_ref - pel_fb;
    /* PID with feedforward terms added */
    static double iz=0;
    iz += eaz * 0.001;
    double u = 10.0*eaz + 0.01*iz;
    if(uaz)*uaz=u; if(uel)*uel=eel*10.0;
}
