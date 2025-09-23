#include "fractol.h"

int args_validator(int argc, char **argv)
{
    if (argc == 4)
    {
        if(!ft_isdouble(argv[2]))
            return (0);
        if(!ft_isdouble(argv[3]))
            return (0);
    }
    return (1);
}