#include "../fractol.h"

void	mandelbrot(int argc, char **argv, t_mlx_data mlx_data)
{
	int	i;

	i = 0;
	if (argc == 3)
	{
		if(iter_controller(argv[2]))
		{
			mlx_data.max_iter = ft_atoi(argv[2]);
			if (mlx_data.max_iter <= 0)
			{
				ft_printf("Expected a positive INT for maximum iterations\n");
				cleanup_mlx(&mlx_data);
				exit(1);
			}
		}
		else
		{
			ft_printf("Expected an INT for maximum iterations\n");
			cleanup_mlx(&mlx_data);
			exit(1);
		}
	}
	mlx_data.fractal_type = 0;
	generate_fractal(&mlx_data, 0);
}

static int	julia_validator(char **argv, t_mlx_data mlx_data)
{
	if(iter_controller(argv[4]))
	{
		mlx_data.max_iter = ft_atoi(argv[4]);
		if(mlx_data.max_iter <= 0)
		{
			ft_printf("Expected a positive INT for maximum iterations for julia's set\n");
			return (0);
		}
	}
	return (1);
}

void	julia(char **argv, t_mlx_data mlx_data)
{
	size_t	i;
	Complex	c;
	int	validator;

	validator = julia_validator(argv, mlx_data);
	i = 0;
	if(ft_issign(argv[2][0]))
		i = 1;
	while(i < ft_strlen(argv[2]))
	{
		if(!ft_isdigit(argv[2][i]) && argv[2][i] != '.')
		{
			ft_printf("Error: '%s' is not a valid number for real part\n", argv[2]);
			exit(3);
		}
		i++;
	}

	i = 0;
	if(argv[3][0] == '-' || argv[3][0] == '+')
		i = 1;
	while(i < ft_strlen(argv[3]))
	{
		if(!ft_isdigit(argv[3][i]) && argv[3][i] != '.')
		{
			ft_printf("Error: '%s' is not a valid number for imaginary part\n", argv[3]);
			exit(3);
		}
		i++;
	}
	mlx_data.fractal_type = 1;
	c.real = ft_atof(argv[2]);
	c.imag = ft_atof(argv[3]);
	mlx_data.julia_c = c;
	generate_fractal(&mlx_data, 1);
}
