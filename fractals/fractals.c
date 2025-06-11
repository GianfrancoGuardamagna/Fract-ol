#include "fractol.h"

void generate_fractal(t_mlx_data *data, int fractal_type) {
    int y = 0;
    int x = 0;
    double range = 4.0 / data->zoom;

    while (y < SIDE_LEN) {
        x = 0;
        while (x < SIDE_LEN) {
            // Map pixels to complex plane
            double real = (x - SIDE_LEN / 2.0) * range / SIDE_LEN + data->center_x;
            double imag = (y - SIDE_LEN / 2.0) * range / SIDE_LEN + data->center_y;
            
            int iter;
            Complex point = {real, imag};
            
            // Choose appropriate iterator based on fractal type
            if(fractal_type == 0)
                iter = mandelbrot_iterator(point, data->max_iter);
            else if(fractal_type == 1)
                iter = julia_iterator(point, data->julia_c, data->max_iter);
            else if(fractal_type == 2)
                iter = burning_ship_iterator(point, data->max_iter);

            int color = calculate_fractal_color(*data, iter, data->max_iter);
            my_pixel_put(&data->img, x, y, color);
            x++;
        }
        y++;
    }

    // Display the image
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->img.img_ptr, 0, 0);
}