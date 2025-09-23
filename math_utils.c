#include "fractol.h"

/*Linear Interpolation: Its used to rescale within the same unit*/
double  map_pixels(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min);
}

t_complex square(t_complex z)
{
    t_complex res;
    res.real = z.real * z.real - z.img * z.img;
    res.img = 2 * z.real * z.img;
    return res;
}

t_complex add(t_complex a, t_complex b)
{
    t_complex res;
    res.real = a.real + b.real;
    res.img = a.img + b.img;
    return res;
}
