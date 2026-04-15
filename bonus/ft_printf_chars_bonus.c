/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chars_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putchar_bonus(t_format *f, int c, int *count)
{
	int	wpad;

	wpad = 0;
	if (f->width > 1)
		wpad = f->width - 1;
	if (!f->left_align)
		ft_putpad(wpad, ' ', count);
	ft_putchar_count((char)c, count);
	if (f->left_align)
		ft_putpad(wpad, ' ', count);
}

void	ft_putstr_bonus(t_format *f, char *s, int *count)
{
	int	slen;
	int	wpad;

	if (!s)
		s = "(null)";
	slen = ft_mystrlen(s);
	if (f->precision >= 0 && f->precision < slen)
		slen = f->precision;
	wpad = 0;
	if (f->width > slen)
		wpad = f->width - slen;
	if (!f->left_align)
		ft_putpad(wpad, ' ', count);
	ft_putmem_count(s, slen, count);
	if (f->left_align)
		ft_putpad(wpad, ' ', count);
}
