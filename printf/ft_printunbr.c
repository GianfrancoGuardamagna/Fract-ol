/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                        :+:      :+:    : */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:59 by gguardam          #+#    #+#             */
/*   Updated: 2025/05/14 14:07:58 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_recursiveunbr(unsigned int n)
{
	int		count;
	char	digit;

	count = 0;
	if (n / 10)
		count += ft_recursiveunbr(n / 10);
	digit = (n % 10) + '0';
	count += write(1, &digit, 1);
	return (count);
}

int	ft_printunbr(unsigned int number)
{
	long	n;
	int		count;

	n = number;
	count = 0;
	count += ft_recursiveunbr(n);
	return (count);
}
