#include "fractol.h"

void cleanup_mlx(t_mlx_data *mlx_data)
{
	if (mlx_data->img.img_ptr)
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img.img_ptr);
	if (mlx_data->mlx_window)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->mlx_window);
	if (mlx_data->mlx_ptr)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

int key_hook(int keycode, t_mlx_data *mlx_data)
{
	double move_factor;

	move_factor = 0.1 / mlx_data->zoom;
	if (keycode == ESC_KEY)
		mlx_loop_end(mlx_data->mlx_ptr);
	else if(keycode == 32)
	{
		mlx_data->zoom = 1;
		mlx_data->center_x = 0;
		mlx_data->center_y = 0;
		generate_fractal(mlx_data, mlx_data->fractal_type);
	}
	else if (keycode == UP_KEY)
	{
		mlx_data->center_y -= move_factor;
		generate_fractal(mlx_data, mlx_data->fractal_type);
	}
	else if (keycode == DOWN_KEY)
	{
		mlx_data->center_y += move_factor;
		generate_fractal(mlx_data, mlx_data->fractal_type);
	}
	else if (keycode == LEFT_KEY)
	{
		mlx_data->center_x -= move_factor;
		generate_fractal(mlx_data, mlx_data->fractal_type);
	}
	else if (keycode == RIGHT_KEY)
	{
		mlx_data->center_x += move_factor;
		generate_fractal(mlx_data, mlx_data->fractal_type);
	}
	else if (keycode == C_KEY)
	{
		if(mlx_data->color_palette != 3)
		{
			mlx_data->color_palette++;
			generate_fractal(mlx_data, mlx_data->fractal_type);
		}
		else
		{
			mlx_data->color_palette = 0;
			generate_fractal(mlx_data, mlx_data->fractal_type);
		}
	}
	return(0);
}

int mouse_wheel_hook(int button, int x, int y, t_mlx_data *mlx_data)
{
	double mouse_re;
	double mouse_im;
	double zoom_factor;

	mouse_re = (x - SIDE_LEN / 2.0) * (4.0 / (SIDE_LEN * mlx_data->zoom)) + mlx_data->center_x;
	mouse_im = (y - SIDE_LEN / 2.0) * (4.0 / (SIDE_LEN * mlx_data->zoom)) + mlx_data->center_y;

	if (button == 4) // Zoom in
	{
		zoom_factor = 1.1;
		mlx_data->zoom *= zoom_factor;
	}
	else if (button == 5) // Zoom out
	{
		zoom_factor = 1/1.1;
		mlx_data->zoom *= zoom_factor;
	}
	else
		return (0);

	// Ajustar el centro para que el zoom se centre en el ratón
	mlx_data->center_x = mouse_re - (mouse_re - mlx_data->center_x) / zoom_factor;
	mlx_data->center_y = mouse_im - (mouse_im - mlx_data->center_y) / zoom_factor;

	// Volver a renderizar el fractal
	generate_fractal(mlx_data, mlx_data->fractal_type);
	return (0);
}

int close_hook(t_mlx_data *mlx_data)
{
	mlx_loop_end(mlx_data->mlx_ptr);
	return (0);
}

void my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	//🚨 Line len is in bytes. WIDTH 400 len_line ~1600 (can differ for alignment). Because 4 bytes per pixel to represent a colour.
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

//it transforms the indiviual numbers into one big 32 bits number. It displace the red 16 positions to the left, the green 8, and the blue stays in place. So now you have one number compound by the initial three.
int	encode_rgb(byte red, byte green, byte blue)
{
	return (red << 16 | green << 8 | blue);
}

void mlx_hooks(t_mlx_data mlx_data)
{
	mlx_hook(mlx_data.mlx_window, 4, 1L<<2, mouse_wheel_hook, mlx_data);
	mlx_key_hook(mlx_data.mlx_window, key_hook, mlx_data);
	// mlx_mouse_hook(mlx_data.mlx_window, key_hook, &mlx_data); Solo reconoce los clicks
	mlx_hook(mlx_data.mlx_window, 17, 0, close_hook, mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
}
