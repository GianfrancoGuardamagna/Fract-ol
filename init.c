/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:20:28 by gguardam          #+#    #+#             */
/*   Updated: 2025/09/30 15:20:29 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fractal_cleanup(t_fractal *fractal)
{
	ft_printf("Failed data loading in structure");
	if (fractal->img.img_ptr)
		mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	if (fractal->mlx_window)
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	if (fractal->mlx_connection)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
	}
	exit(1);
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, KeyPress, \
KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->mlx_window, ButtonPress, \
ButtonPressMask, mouse_handler, fractal);
	mlx_hook(fractal->mlx_window, DestroyNotify, \
StructureNotifyMask, close_handler, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (!fractal->mlx_connection)
		fractal_cleanup(fractal);
	fractal->mlx_window = \
mlx_new_window(fractal->mlx_connection, SIDE_LEN, SIDE_LEN, "Fract'ol");
	if (!fractal->mlx_window)
		fractal_cleanup(fractal);
	fractal->img.img_ptr = \
mlx_new_image(fractal->mlx_connection, SIDE_LEN, SIDE_LEN);
	if (!fractal->img.img_ptr)
		fractal_cleanup(fractal);
	fractal->img.pixels_ptr = \
mlx_get_data_addr(fractal->img.img_ptr, \
&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	if (!fractal->img.pixels_ptr)
		fractal_cleanup(fractal);
	fractal->max_iterations = 500;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1;
	events_init(fractal);
}
