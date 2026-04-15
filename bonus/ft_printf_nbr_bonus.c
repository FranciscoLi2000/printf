/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putnbr_bonus(t_format *f, int n, int *count)
{
	char			digits[21];
	const char		*pfx;
	unsigned long	abs_n;
	int				dlen;

	if (n < 0)
	{
		abs_n = (unsigned long)(-(long)n);
		pfx = "-";
	}
	else
	{
		abs_n = (unsigned long)n;
		if (f->space)
			pfx = " ";
		else
			pfx = "";
	}
	dlen = ft_uitoa_base(abs_n, 10, 0, digits);
	if (f->precision == 0 && abs_n == 0)
		dlen = 0;
	ft_print_num(pfx, digits, dlen, f, count);
}
