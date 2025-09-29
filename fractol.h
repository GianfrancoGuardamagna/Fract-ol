#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define SIDE_LEN 400
# define BLUE 0x0033A0
# define YELLOW 0xFFCC00
# define BLACK 0x000000

/*Complex Number = {a + b*i } being 'a' the real part/
and 'b*i' the imaginary part*/
typedef struct s_complex
{
	double	real;
	double	img;
}	t_complex;

/*This is a pixel buffer, values will come from mlx_get_addr()*/
typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

/*
void    *mlx_connection = mlx_init()
void    *mlx_window = mlx_new_window()
*/
typedef struct s_fractal
{
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	int		max_iterations;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_real;
	double	julia_img;
	int		fractal_type;
}	t_fractal;

/*Parser*/
int			args_validator(int argc, char **argv);

/*Math Utils*/
double		map_pixels(double unscaled_num);
t_complex	add(t_complex a, t_complex b);
t_complex	square(t_complex z);

/*Init*/
void		fractal_init(t_fractal *fractal);

/*Render*/
void		fractal_render(t_fractal *fractal);

/*events*/
int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);

#endif