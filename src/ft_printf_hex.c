/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunbr_count(unsigned long n, unsigned int base,
			int uppercase, int *count)
{
	const char	*digits;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	if (n >= base)
		ft_putunbr_count(n / base, base, uppercase, count);
	ft_putchar_count(digits[n % base], count);
}

void	ft_putptr_count(void *ptr, int *count)
{
	if (!ptr)
	{
		ft_putstr_count("(nil)", count);
		return ;
	}
	ft_putstr_count("0x", count);
	ft_putunbr_count((unsigned long)ptr, 16, 0, count);
}
