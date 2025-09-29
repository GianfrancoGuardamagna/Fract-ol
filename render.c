#include "fractol.h"

static int	mandelbrot_iterator(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.real = 0;
	z.img = 0;
	c.real = map_pixels(x) * fractal->zoom + fractal->shift_x;
	c.img = map_pixels(y) * fractal->zoom + fractal->shift_y;
	i = 0;
	while (i < fractal->max_iterations)
	{
		z = add(square(z), c);
		if (z.real * z.real + z.img * z.img > 4.0)
			return (i);
		i++;
	}
	return (fractal->max_iterations);
}

static int	julia_iterator(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.real = map_pixels(x) * fractal->zoom + fractal->shift_x;
	z.img = map_pixels(y) * fractal->zoom + fractal->shift_y;
	c.real = fractal->julia_real;
	c.img = fractal->julia_img;
	i = 0;
	while (i < fractal->max_iterations)
	{
		z = add(square(z), c);
		if (z.real * z.real + z.img * z.img > 4.0)
			return (i);
		i++;
	}
	return (fractal->max_iterations);
}

static void	pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static int	shade_color(int base, double factor)
{
	int	r;
	int	g;
	int	b;

	r = (base >> 16) & 0xFF;
	g = (base >> 8) & 0xFF;
	b = base & 0xFF;
	r *= factor;
	g *= factor;
	b *= factor;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;
	int	iter;
	int	color;

	y = 0;
	while (y < SIDE_LEN)
	{
		x = 0;
		while (x < SIDE_LEN)
		{
			if (!fractal->fractal_type)
				iter = mandelbrot_iterator(x, y, fractal);
			else
				iter = julia_iterator(x, y, fractal);
			if (iter == fractal->max_iterations)
				color = YELLOW;
			else if (iter < fractal->max_iterations)
				color = shade_color(BLUE, (double)(iter % 50) / 50.0);
			pixel_put(&fractal->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window, \
fractal->img.img_ptr, 0, 0);
}
