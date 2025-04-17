#include "ft_printf.h"

void	ft_putstr(char *s, int *count)
{
	if (!s)
	{
		write(1, "(null)", 6);
		count += 6;
	}
	else
	{
		while (*s)
		{
			ft_putchar(*s, count);
			s++;
		}
	}
}
