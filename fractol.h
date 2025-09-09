/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:00:00 by gguardam          #+#    #+#             */
/*   Updated: 2025/09/09 15:58:29 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "printf/ft_printf.h"

# define MALLOC_ERROR 1
# define SIDE_LEN 1400
# define ESC_KEY 65307
# define SPACE_KEY 32
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define C_KEY 99

static const int first_colors[5] = {
	0xff3c00,
	0xff6e00,
	0xffd500,
	0x00e677,
	0x00aeff
};

static const int second_colors[5] = {
	0x1a1aff,
	0x3399ff,
	0x33ffcc,
	0xffff66,
	0xff3385
};

static const int third_colors[5] = {
	0x4b0082,
	0x8a2be2,
	0x00ced1,
	0x7fff00,
	0xffd700
};

typedef unsigned char	byte;

typedef struct {
	double	real;
	double	imag;
}	Complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_window;
	t_img	img;
	double	zoom;
	double	center_x;
	double	center_y;
	int		max_iter;
	int		color_palette;
	int		fractal_type;
	Complex	julia_c;
}	t_mlx_data;

Complex		square(Complex z);
Complex		add(Complex a, Complex b);
int			mandelbrot_iterator(Complex c, int maxIter);
int			julia_iterator(Complex z, Complex c, int maxIter);
int			burning_ship_iterator(Complex c, int maxIter);
void		my_pixel_put(t_img *img, int x, int y, int color);
int			encode_rgb(byte red, byte green, byte blue);
void 		generate_fractal(t_mlx_data *data, int fractal_type);
int			calculate_fractal_color(t_mlx_data data, int iter, int max_iter);
void		cleanup_mlx(t_mlx_data *mlx_data);
int			key_hook(int keycode, t_mlx_data *mlx_data);
int			close_hook(t_mlx_data *mlx_data);
t_mlx_data  mlx_initiator(t_mlx_data mlx_data);
void 		mlx_hooks(t_mlx_data mlx_data);

//Input Controller
void	mandelbrot(int argc, char **argv, t_mlx_data mlx_data);
void	julia(char **argv, t_mlx_data mlx_data);
int		iter_controller(char *str);

#endif