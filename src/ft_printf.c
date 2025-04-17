#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			parse_format(&format, ap, &count);
		}
		else
			ft_putchar(*format++, &count);
	}
	va_end(ap);
	return (count);
}
