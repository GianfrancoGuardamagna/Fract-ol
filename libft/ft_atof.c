/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:21:05 by gguardam          #+#    #+#             */
/*   Updated: 2025/05/06 14:28:11 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static float	parse_fraction(const char *str, int *i)
{
	float	res;
	float	dec;
	int		dot;

	res = 0;
	dec = 0.1;
	dot = 0;
	while ((ft_isdigit(str[*i])) || (str[*i] == '.' && !dot))
	{
		if (str[*i] == '.')
			dot = 1;
		else if (!dot)
			res = res * 10 + (str[*i] - '0');
		else
		{
			res += (str[*i] - '0') * dec;
			dec /= 10;
		}
		(*i)++;
	}
	return (res);
}

float	ft_atof(const char *str)
{
	int		i;
	int		sign;
	float	res;

	i = 0;
	while (is_space(str[i]))
		i++;
	sign = get_sign(str, &i);
	res = parse_fraction(str, &i);
	return (res * sign);
}
