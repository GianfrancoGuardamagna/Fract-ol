#include "fractol.h"

void cleanup_mlx(t_mlx_data *mlx_data)
{
    if (mlx_data->img.img_ptr)
        mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img.img_ptr);
    if (mlx_data->mlx_window)
        //Destroyed to free the mallocs like the other functions, also it frees the '*mlx_window'
        mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->mlx_window);
    if (mlx_data->mlx_ptr)
    {
        //We should free the mallocs made on the initialitation of the X Server.
        mlx_destroy_display(mlx_data->mlx_ptr);
        free(mlx_data->mlx_ptr);
    }
}

// Event handler to close window with ESC key
int key_hook(int keycode, t_mlx_data *mlx_data)
{
    ft_printf("Keycode presionado: %d\n%d\n", keycode, SPACE_KEY);
    double move_factor = 0.1 / mlx_data->zoom;

    if (keycode == ESC_KEY)
        mlx_loop_end(mlx_data->mlx_ptr);
    else if(keycode == 32)
    {
        mlx_data->zoom = 1;
        mlx_data->center_x = 0;
        mlx_data->center_y = 0;
        generate_fractal(mlx_data, mlx_data->fractal_type);
    }
    else if (keycode == UP_KEY) // Move up
    {
        mlx_data->center_y -= move_factor;
        generate_fractal(mlx_data, mlx_data->fractal_type);
    }
    else if (keycode == DOWN_KEY) // Move down
    {
        mlx_data->center_y += move_factor;
        generate_fractal(mlx_data, mlx_data->fractal_type);
    }
    else if (keycode == LEFT_KEY) // Left arrow
    {
        mlx_data->center_x -= move_factor;
        generate_fractal(mlx_data, mlx_data->fractal_type);
    }
    else if (keycode == RIGHT_KEY) // Right arrow
    {
        mlx_data->center_x += move_factor;
        generate_fractal(mlx_data, mlx_data->fractal_type);
    }
    else if (keycode == C_KEY)
    {
        if(mlx_data->color_palette != 3)
        {
            mlx_data->color_palette++;
            generate_fractal(mlx_data, mlx_data->fractal_type);
        }
        else
        {
            mlx_data->color_palette = 0;
            generate_fractal(mlx_data, mlx_data->fractal_type);
        }
    }
    return(0);
}

int mouse_wheel_hook(int button, int x, int y, t_mlx_data *mlx_data)
{
    double mouse_re;
    double mouse_im;
    double zoom_factor;

    // Convert mouse con Complex Coordinates
    mouse_re = (x - SIDE_LEN / 2.0) * (4.0 / (SIDE_LEN * mlx_data->zoom)) + mlx_data->center_x;
    mouse_im = (y - SIDE_LEN / 2.0) * (4.0 / (SIDE_LEN * mlx_data->zoom)) + mlx_data->center_y;

    if (button == 4) // Zoom in
    {
        zoom_factor = 1.1;
        mlx_data->zoom *= zoom_factor;
    }
    else if (button == 5) // Zoom out
    {
        zoom_factor = 1/1.1;
        mlx_data->zoom *= zoom_factor;
    }
    else
        return (0);

    // Ajustar el centro para que el zoom se centre en el ratón
    mlx_data->center_x = mouse_re - (mouse_re - mlx_data->center_x) / zoom_factor;
    mlx_data->center_y = mouse_im - (mouse_im - mlx_data->center_y) / zoom_factor;

    // Volver a renderizar el fractal
    generate_fractal(mlx_data, mlx_data->fractal_type);
    return (0);
}

// Event handler for window close button (X)
int close_hook(t_mlx_data *mlx_data)
{
    mlx_loop_end(mlx_data->mlx_ptr);
    return (0);
}

void my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	//🚨 Line len is in bytes. WIDTH 400 len_line ~1600 (can differ for alignment). Because 4 bytes per pixel to represent a colour.
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

//it transforms the indiviual numbers into one big 32 bits number. It displace the red 16 positions to the left, the green 8, and the blue stays in place. So now you have one number compound by the initial three.
int	encode_rgb(byte red, byte green, byte blue)
{
    return (red << 16 | green << 8 | blue);
}

void mlx_hooks(t_mlx_data mlx_data)
{
        /* Set up event handlers
        // This function will keep track of the different events that the client trigger with the keyboard or mouse.
        // It need the first param as window, the second is a function that handle the input, and the pointer to X Server.
        // 'key_hook' function will recived as first parameter the input as INT, indistinctly from the key.
        */
        mlx_hook(mlx_data.mlx_window, 4, 1L<<2, mouse_wheel_hook, &mlx_data);
        mlx_key_hook(mlx_data.mlx_window, key_hook, &mlx_data);
        // mlx_mouse_hook(mlx_data.mlx_window, key_hook, &mlx_data); Solo reconoce los clicks

        /* Window close event
        // This function will keep track of the different events forwarded from the window.
        // In this case, has the window as first param, the number of the event that in this case is 17 because of X11 protocol.
        // The third param '0', will be the masc, and the last param is a pointer to the display.
        // Events (like ButtonPress): Describe the actual event type, such as pressing a button or moving the mouse.

        //Event Masks (like ButtonPressMask): Are filters that determine which types of events a program wants 
        //to listen for. By setting a specific mask, you're saying, "Notify me when this type of event happens."
        */
        mlx_hook(mlx_data.mlx_window, 17, 0, close_hook, &mlx_data);

        /* EVENT LOOP
        Without this loop the process will stop immediately
        
        * The minilibx library has a function called mlx_loop. 
        * This function starts what's known as an event loop. 
        * An event loop keeps the application running and constantly 
        * checks for events, such as user input (like mouse clicks or keyboard presses). 
        * As long as the application is running, this loop continues to execute.

        The concept can be likened to:

            while (application is running) 
            {
                check for events;
                    execute associated functions for those events;
            }
        */
        mlx_loop(mlx_data.mlx_ptr); //Carefull with this loops because without escape or close event, it forces you to shut down the process, never freeing the memory allocated;
}