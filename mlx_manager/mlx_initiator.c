#include "fractol.h"

t_mlx_data    mlx_initiator(t_mlx_data mlx_data)
{
	mlx_data.mlx_window = mlx_new_window(mlx_data.mlx_ptr, SIDE_LEN, SIDE_LEN, "Fract'ol");
	mlx_data.img.img_ptr = mlx_new_image(mlx_data.mlx_ptr, SIDE_LEN, SIDE_LEN);
	if (mlx_data.img.img_ptr == NULL || mlx_data.mlx_window == NULL)
	{
		cleanup_mlx(&mlx_data);
		ft_printf("Malloc error initiating mlx\n");
		exit(1);
	}
	mlx_data.img.img_pixels_ptr = mlx_get_data_addr(
		mlx_data.img.img_ptr,
		&mlx_data.img.bits_per_pixel,
		&mlx_data.img.line_len,
		&mlx_data.img.endian
	);
	mlx_data.max_iter = 500;
	mlx_data.zoom = 1.0;
	mlx_data.center_x = 0.0;
	mlx_data.center_y = 0.0;
	mlx_data.color_palette = 0;
	return (mlx_data);
}
