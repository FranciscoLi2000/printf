#include "ft_printf.h"

int	parse_format(const char **format, va_list ap, int *count)
{
	if (**format == 'c')
		ft_putchar(va_arg(ap, int), count);
	else if (**format == 's')
		ft_putstr(va_arg(ap, char *), count);
	else if (**format == 'd' || **format == 'i')
		ft_putnbr(va_arg(ap, int), count);
	else if (**format == 'u')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", count);
	else if (**format == 'x')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", count);
	else if (**format == 'X')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", count);
	else if (**format == 'p')
		ft_putptr(va_arg(ap, void *), count);
	else if (**format == '%')
		ft_putchar('%', count);
	(*format)++;
	return (*count);
}
