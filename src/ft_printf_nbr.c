/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_pos(unsigned long n, int *count)
{
	if (n >= 10)
		ft_putnbr_pos(n / 10, count);
	ft_putchar_count('0' + (n % 10), count);
}

void	ft_putnbr_count(int n, int *count)
{
	unsigned long	uval;

	if (n < 0)
	{
		ft_putchar_count('-', count);
		uval = (unsigned long)(-(long)n);
	}
	else
		uval = (unsigned long)n;
	ft_putnbr_pos(uval, count);
}
