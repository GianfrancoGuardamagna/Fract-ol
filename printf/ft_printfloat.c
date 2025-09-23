#include "ft_printf.h"

static int ft_recursivenbr(long n)
{
    int	count;
    char digit;

    count = 0;
    if (n / 10)
        count += ft_recursivenbr(n / 10);
    digit = (n % 10) + '0';
    count += write(1, &digit, 1);
    return (count);
}

int ft_printfloat(float number)
{
    int count;
    long int_part;
    long frac_part;
    double temp;
    int divisor;
    char c;

    count = 0;
    temp = (double)number;
    if (temp < 0)
    {
        count += write(1, "-", 1);
        temp = -temp;
    }
    temp += 0.0000005;
    int_part = (long)temp;
    count += ft_recursivenbr(int_part);
    count += write(1, ".", 1);
    frac_part = (long)((temp - int_part) * 1000000);
    divisor = 100000;
    while (divisor >= 1)
    {
        c = (frac_part / divisor) + '0';
        count += write(1, &c, 1);
        frac_part %= divisor;
        divisor /= 10;
    }
    return count;
}
