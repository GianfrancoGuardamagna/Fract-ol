#include "ft_printf.h"

static int ft_recursiveunbr(unsigned int n)
{
	int	count;
	char digit;

	count = 0;
    if (n / 10)
		count += ft_recursiveunbr(n / 10);
    digit = (n % 10) + '0';
    count += write(1, &digit, 1);
	return (count);
}

int ft_printunbr(unsigned int number)
{
	long	n;
	int	count;

	n = number;
	count = 0;
	count += ft_recursiveunbr(n);
	return (count);
}