#include "ft_printf.h"
#include <string.h>

int ft_printstr(char *stringy)
{
	int len;

	if (!stringy)
		return write(1, "(null)", 6);
	len = strlen(stringy);
	write(1, stringy, len);
	return (len);
}