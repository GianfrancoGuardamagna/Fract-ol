#include "fractol.h"

/*Linear Interpolation: Its used to rescale within the same unit*/
double	map_pixels(double unscaled_num)
{
	return (((2) - (-2)) * unscaled_num / SIDE_LEN + (-2));
}

t_complex	square(t_complex z)
{
	t_complex	res;

	res.real = z.real * z.real - z.img * z.img;
	res.img = 2 * z.real * z.img;
	return (res);
}

t_complex	add(t_complex a, t_complex b)
{
	t_complex	res;

	res.real = a.real + b.real;
	res.img = a.img + b.img;
	return (res);
}
