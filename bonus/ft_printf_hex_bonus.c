/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putu_bonus(t_format *f, unsigned int n, int *count)
{
	char	digits[21];
	int		dlen;

	dlen = ft_uitoa_base((unsigned long)n, 10, 0, digits);
	if (f->precision == 0 && n == 0)
		dlen = 0;
	ft_print_num("", digits, dlen, f, count);
}

void	ft_puthex_bonus(t_format *f, unsigned int n, int upper, int *count)
{
	char		digits[21];
	const char	*pfx;
	int			dlen;

	dlen = ft_uitoa_base((unsigned long)n, 16, upper, digits);
	if (f->precision == 0 && n == 0)
		dlen = 0;
	pfx = "";
	if (f->hash && n != 0)
	{
		if (upper)
			pfx = "0X";
		else
			pfx = "0x";
	}
	ft_print_num(pfx, digits, dlen, f, count);
}

void	ft_putptr_bonus(t_format *f, void *ptr, int *count)
{
	char	digits[21];
	int		dlen;
	int		wpad;

	if (!ptr)
	{
		wpad = 0;
		if (f->width > 5)
			wpad = f->width - 5;
		if (!f->left_align)
			ft_putpad(wpad, ' ', count);
		ft_putmem_count("(nil)", 5, count);
		if (f->left_align)
			ft_putpad(wpad, ' ', count);
		return ;
	}
	dlen = ft_uitoa_base((unsigned long)ptr, 16, 0, digits);
	ft_print_num("0x", digits, dlen, f, count);
}
