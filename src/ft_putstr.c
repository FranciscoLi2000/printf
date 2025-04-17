#include "ft_printf.h"

void	ft_print_str(char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
		ft_putchar(*s++, count);
}
