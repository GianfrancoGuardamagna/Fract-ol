#include "ft_printf.h"

int ft_printhex(unsigned int numby, char *hex)
{
    char c;
    int count;

    count = 0;
    if (numby >= 16)
        count += ft_printhex(numby / 16, hex);
    c = hex[numby % 16];
    count += write(1, &c, 1);

    return (count);
}