#include "ft_printf.h"

static void	convert_to_hex(uintptr_t ptr_val, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (ptr_val >= 16)
		convert_to_hex((ptr_val / 16), count);
	ft_putchar(base[ptr_val % 16], count);
}

void	ft_putptr(void *ptr, int *count)
{
	if (ptr == NULL)
		ft_putstr("(nil)", count);
	else
	{
		ft_putstr("0x", count);
		convert_to_hex((uintptr_t)ptr, count);
	}
}
