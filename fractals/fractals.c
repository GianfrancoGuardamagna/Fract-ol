#include "fractol.h"

void generate_fractal(t_mlx_data *data, int fractal_type) {
	int y;
	int x;
	double range;
	int iter;
	double real;
	double imag;
	Complex point;
	int color;

	range = 4.0 / data->zoom;
	y = 0;
	while (y < SIDE_LEN)
	{
		x = 0;
		while (x < SIDE_LEN)
		{
			// real = (x - SIDE_LEN / 2.0) * range / SIDE_LEN + data->center_x;
			// imag = (y - SIDE_LEN / 2.0) * range / SIDE_LEN + data->center_y;
			real = (x - SIDE_LEN / 2.0) * range / SIDE_LEN;
			imag = (y - SIDE_LEN / 2.0) * range / SIDE_LEN;
			iter = 0;
			point.real = real;
			point.imag = imag;
			if(fractal_type == 0)
				iter = mandelbrot_iterator(point, data->max_iter);
			else if(fractal_type == 1)
				iter = julia_iterator(point, data->julia_c, data->max_iter);
			else if(fractal_type == 2)
				iter = burning_ship_iterator(point, data->max_iter);
			color = calculate_fractal_color(*data, iter, data->max_iter);
			my_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->img.img_ptr, 0, 0);
}
