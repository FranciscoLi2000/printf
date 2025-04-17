#include "ft_printf.h"

#define INT_MIN -2147483648

void	ft_putnbr(int nbr, int *count)
{
	int	num;

	if (nbr == INT_MIN)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar('-', count);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		num = nbr / 10;
		ft_putnbr(num, count);
	}
	ft_putchar(nbr % 10 + '0', count);
}
