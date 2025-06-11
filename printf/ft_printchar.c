#include "ft_printf.h"

int ft_printchar(char  charsy)
{
    charsy = (unsigned char) charsy;
    return write(1, &charsy, 1);
}