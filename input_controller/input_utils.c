#include "../fractol.h"

int	iter_controller(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
		{
			ft_printf("Expected a INT for iterations\n");
			return (0);
		}
		i++;
	}
	return (1);
}