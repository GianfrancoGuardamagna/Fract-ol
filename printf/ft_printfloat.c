/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfloat.c                                        :+:      :+:    : */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:59 by gguardam          #+#    #+#             */
/*   Updated: 2025/05/14 14:07:58 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_recursivenbr(long n)
{
	int		count;
	char	digit;

	count = 0;
	if (n / 10)
		count += ft_recursivenbr(n / 10);
	digit = (n % 10) + '0';
	count += write(1, &digit, 1);
	return (count);
}

static int	print_fraction(long frac, int precision)
{
	int		count;
	int		divisor;
	char	c;

	count = 0;
	divisor = 1;
	while (precision-- > 1)
		divisor *= 10;
	while (divisor >= 1)
	{
		c = (frac / divisor) + '0';
		count += write(1, &c, 1);
		frac %= divisor;
		divisor /= 10;
	}
	return (count);
}

static int	handle_sign(double *num)
{
	int	count;

	count = 0;
	if (*num < 0)
	{
		count += write(1, "-", 1);
		*num = -*num;
	}
	return (count);
}

int	ft_printfloat(float number)
{
	int		count;
	long	int_part;
	long	frac_part;
	double	temp;
	int		precision;

	count = 0;
	precision = 6;
	temp = (double)number + 0.0000005;
	count += handle_sign(&temp);
	int_part = (long)temp;
	count += ft_recursivenbr(int_part);
	count += write(1, ".", 1);
	frac_part = (long)((temp - int_part) * 1000000);
	count += print_fraction(frac_part, precision);
	return (count);
}
