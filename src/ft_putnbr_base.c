#include "ft_printf.h"

void	ft_putnbr_base(unsigned int nbr, char *base, int *count)
{
	unsigned int	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (base_len < 2)
		return ;
	if (nbr >= base_len)
		ft_putnbr_base((nbr / base_len), base, count);
	ft_putchar(base[nbr % base_len], count);
}
