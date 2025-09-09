/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:46:16 by gguardam          #+#    #+#             */
/*   Updated: 2025/09/09 18:19:37 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;

	if (argc < 2)
	{
		ft_printf("Invalid params");
		return (1);
	}
	mlx_data.mlx_ptr = mlx_init();
	if (mlx_data.mlx_ptr == NULL)
	{
		ft_printf("Malloc error initiating mlx\n");
		exit(1);
	}
	mlx_data = mlx_initiator(mlx_data);
	if (!ft_strncmp(argv[1], "mandelbrot", 10))
		mandelbrot(argc, argv, mlx_data);
	//else if (!ft_strncmp(argv[1], "julia", 5))
		//julia(argc, argv, mlx_data);
	//else if (!ft_strncmp(argv[1], "burning_ship", 12))
		//burning_ship(argc, argv, mlx_data);
	else
	{
		ft_printf("Incorrect Params\n");
		cleanup_mlx(&mlx_data);
		return (1);
	}
	mlx_hooks(mlx_data);
	cleanup_mlx(&mlx_data);
	return (0);
}
