#include "fractol.h"

static int	ft_isdouble(char *str)
{
	int	i;
	int	has_digit;
	int	has_dot;

	i = 0;
	has_digit = 0;
	has_dot = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digit = 1;
		else if (str[i] == '.' && !has_dot)
			has_dot = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}

int	args_validator(int argc, char **argv)
{
	if (argc == 4)
	{
		if (!ft_isdouble(argv[2]))
			return (0);
		if (!ft_isdouble(argv[3]))
			return (0);
	}
	return (1);
}
