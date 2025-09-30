/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:20:31 by gguardam          #+#    #+#             */
/*   Updated: 2025/09/30 15:20:32 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10)) || \
(argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		if (!args_validator(argc, argv))
			return (ft_printf("Error: Julia expects doubles as parameters\n"));
		fractal_init(&fractal);
		fractal.fractal_type = 0;
		if (argc == 4)
		{
			fractal.fractal_type = 1;
			fractal.julia_real = ft_atof(argv[2]);
			fractal.julia_img = ft_atof(argv[3]);
		}
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_printf("Invalid Inputs:\n{./fractol mandelbrot}\n{./fractol \
julia <real> <imaginary>}\n");
		exit(1);
	}
	return (0);
}
