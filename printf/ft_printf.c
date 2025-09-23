/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:59 by gguardam          #+#    #+#             */
/*   Updated: 2025/05/14 14:07:58 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parameter_manager(char	stringy, va_list vargs)
{
	if (stringy == 'c')
		return (ft_printchar(va_arg(vargs, int)));
	else if (stringy == 's')
		return (ft_printstr(va_arg(vargs, char *)));
    else if (stringy == 'f')
		return (ft_printfloat(va_arg(vargs, double)));
	else if (stringy == 'p')
		return ((ft_printptr(va_arg(vargs, void *))));
	else if (stringy == 'd' || stringy == 'i')
		return (ft_printnbr(va_arg(vargs, int)));
	else if (stringy == 'u')
		return (ft_printunbr(va_arg(vargs, unsigned int)));
	else if (stringy == 'x')
		return (ft_printhex(va_arg(vargs, unsigned int), "0123456789abcdef"));
	else if (stringy == 'X')
		return (ft_printhex(va_arg(vargs, unsigned int), "0123456789ABCDEF"));
	else if (stringy == '%')
		return (write(1, "%", 1));
    return (0);
}

int ft_printf(char const *stringy, ...)
{
    va_list vargs;
    int parameters;

    va_start(vargs, stringy);
    parameters = 0;
    while (*stringy != '\0')
    {
        if (*stringy == '%' && *(stringy + 1))
        {   
            stringy++;
            parameters += parameter_manager(*stringy, vargs);
        }
        else
        {
            parameters += write(1, stringy, 1);
        }
        stringy++;
    }
    va_end(vargs);
    return (parameters);
}