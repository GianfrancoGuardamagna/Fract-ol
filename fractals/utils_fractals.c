#include "fractol.h"

Complex square(Complex z) {
    Complex res;
    res.real = z.real * z.real - z.imag * z.imag;
    res.imag = 2 * z.real * z.imag;
    return res;
}

Complex add(Complex a, Complex b) {
    Complex res;
    res.real = a.real + b.real;
    res.imag = a.imag + b.imag;
    return res;
}

int calculate_fractal_color(t_mlx_data data, int iter, int max_iter) {
    // Fondos con gradiente
    int backgrounds[3] = {
        0x2d1b45,  // Morado más claro
        0x1b2d45,  // Azul más claro
        0x452d1b   // Marrón más claro
    };
    
    if (iter == max_iter) {
        return backgrounds[data.color_palette % 3];
    }
    
    // Función más compleja para variaciones de color
    double t = (double)iter / max_iter;
    double freq = t * 6.28318 * 4;
    double spiral = sin(freq) * cos(freq * 0.7) * sin(freq * 1.3);
    double color_pos = (spiral + 1.0) * 2.0; // 0 a 4
    
    // Seleccionar paleta
    const int *current_palette;
    if (data.color_palette == 0)
        current_palette = first_colors;
    else if (data.color_palette == 1)
        current_palette = second_colors;
    else
        current_palette = third_colors;
    
    // Interpolación con efectos especiales
    int index1 = (int)color_pos % 5;
    int index2 = (index1 + 1) % 5;
    double blend = color_pos - (int)color_pos;
    
    int r1 = (current_palette[index1] >> 16) & 0xFF;
    int g1 = (current_palette[index1] >> 8) & 0xFF;
    int b1 = current_palette[index1] & 0xFF;
    
    int r2 = (current_palette[index2] >> 16) & 0xFF;
    int g2 = (current_palette[index2] >> 8) & 0xFF;
    int b2 = current_palette[index2] & 0xFF;
    
    int r = (int)(r1 + (r2 - r1) * blend);
    int g = (int)(g1 + (g2 - g1) * blend);
    int b = (int)(b1 + (b2 - b1) * blend);
    
    // Efecto de brillo pulsante
    double pulse = sin(t * 6.28318 * 2) * 0.3 + 0.7;
    r = (int)(r * pulse);
    g = (int)(g * pulse);
    b = (int)(b * pulse);
    
    // Mantener en rango
    r = r > 255 ? 255 : (r < 0 ? 0 : r);
    g = g > 255 ? 255 : (g < 0 ? 0 : g);
    b = b > 255 ? 255 : (b < 0 ? 0 : b);
    
    return (r << 16) | (g << 8) | b;
}
