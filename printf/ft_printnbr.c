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

int ft_printnbr(int number)
{
	long	n;
	int	count;

	n = number;
	count = 0;
	if(n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	count += ft_recursivenbr(n);
	return (count);
}