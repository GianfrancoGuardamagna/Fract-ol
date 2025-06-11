#include "fractol.h"

int main(int argc, char **argv)
{
    t_mlx_data mlx_data;

    mlx_data = mlx_initiator(mlx_data);

    mlx_data.max_iter = 500;
    mlx_data.zoom = 1.0;
    mlx_data.center_x = 0.0;
    mlx_data.center_y = 0.0;
    mlx_data.color_palette = 0;

    if(((argc == 2) || (argc == 3)) && !ft_strncmp(argv[1], "mandelbrot", 10))
    {
        if(argc == 3)
        {
            mlx_data.max_iter = ft_atoi(argv[2]);
            if(mlx_data.max_iter <= 0)
            {
                ft_printf("Expected a positive INT for maximum iterations for mandelbrot's set\n");
                exit(1);
            }
        }
        mlx_data.fractal_type = 0;
        generate_fractal(&mlx_data, 0);
    }
    else if(((argc == 4) || (argc == 5)) && !ft_strncmp(argv[1], "julia", 5) && argv[2] && argv[3])
    {
        size_t i;
        Complex c;

        i = 0;
        if(argc == 5)
        {
            mlx_data.max_iter = ft_atoi(argv[4]);
            if(mlx_data.max_iter <= 0)
            {
                ft_printf("Expected a positive INT for maximum iterations for julia's set\n");
                exit(1);
            }
        }
        if(argv[2][0] == '-' || argv[2][0] == '+')
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
    else if(((argc == 2) || (argc == 3)) && !ft_strncmp(argv[1], "burning_ship", 12))
    {
        if(argc == 3)
        {
            mlx_data.max_iter = ft_atoi(argv[2]);
            if(mlx_data.max_iter <= 0)
            {
                ft_printf("Expected a positive INT for maximum iterations for burning ship fractal\n");
                exit(1);
            }
        }
        mlx_data.fractal_type = 2;
        generate_fractal(&mlx_data, 2);
    }
    else
    {
        ft_printf("Please enter the right format:\n\t\"./fractal mandelbrot <max. iterations>\"\t\n\t\"./fractal julia <real> <img> <max. iterations>\"\t\n\t\"./fractal burning_ship <max. iterations>\"\t\n");
        exit(1);
    }
    
    mlx_hooks(mlx_data);

    // Cleanup the memory allocated
    cleanup_mlx(&mlx_data);
    return (0);
}
