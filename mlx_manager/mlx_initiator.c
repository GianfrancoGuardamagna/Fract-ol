#include "fractol.h"

t_mlx_data    mlx_initiator(t_mlx_data mlx_data){
    //mlx_init() returns a pointer to an structure but for the moment lets say that is the connection to the Display of X Server.
        mlx_data.mlx_ptr = mlx_init();
        if (mlx_data.mlx_ptr == NULL)
        {
            ft_printf("Malloc error initiating mlx\n");
            exit(1);
        }

        //mlx_new_window() now returns a pointer to the actual window created by X.
        mlx_data.mlx_window = mlx_new_window(mlx_data.mlx_ptr, SIDE_LEN, SIDE_LEN, "Fract'ol");
        if (mlx_data.mlx_window == NULL)
        {
            cleanup_mlx(&mlx_data);
            ft_printf("Malloc error initiating mlx\n");
            exit(1);
        }

        //this initialize the image pointer where we are going to upload our colour buffer;
        mlx_data.img.img_ptr = mlx_new_image(mlx_data.mlx_ptr, SIDE_LEN, SIDE_LEN);
        if (mlx_data.img.img_ptr == NULL)
        {
            cleanup_mlx(&mlx_data);
            ft_printf("Malloc error initiating mlx\n");
            exit(1);
        }

        /*Here we obtaing the addresses of the pixel buffer
        //When the image was created, every pixel was assigned to a space in memory, with this function we can locate that positions to use or fill with our image.
        */
        mlx_data.img.img_pixels_ptr = mlx_get_data_addr(
            mlx_data.img.img_ptr,
            &mlx_data.img.bits_per_pixel,
            &mlx_data.img.line_len,
            &mlx_data.img.endian
        );

        return (mlx_data);
    }