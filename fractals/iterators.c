#include "fractol.h"

int mandelbrot_iterator(Complex c, int maxIter) {
    Complex z;
    int i;

    z.real = 0.0;
    z.imag = 0.0;
    i = 0;
    while (i < maxIter) {
        z = add(square(z), c);
        if (z.real * z.real + z.imag * z.imag > 4.0)
            return i;
        i++;
    }
    return maxIter;
}

int julia_iterator(Complex z, Complex c, int maxIter) {
    int i;

    i = 0;
    while (i < maxIter) {
        z = add(square(z), c);
        if (z.real * z.real + z.imag * z.imag > 4.0)
            return i;
        i++;
    }
    return maxIter;
}

int burning_ship_iterator(Complex c, int maxIter) {
    Complex z = {0, 0};
    int iter = 0;
    
    while (iter < maxIter) {
        z.real = fabs(z.real);
        z.imag = fabs(z.imag);
        z = add(square(z), c);
        
        if (z.real * z.real + z.imag * z.imag > 4.0)
            return iter;
        iter++;
    }
    return maxIter;
}