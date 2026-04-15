/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putchar_count(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putpad(int n, char c, int *count)
{
	while (n > 0)
	{
		ft_putchar_count(c, count);
		n--;
	}
}

void	ft_putmem_count(const char *s, int n, int *count)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar_count(s[i], count);
		i++;
	}
}

int	ft_mystrlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_uitoa_base(unsigned long n, unsigned int base, int upper, char *buf)
{
	const char	*digs;
	char		tmp[21];
	int			len;
	int			i;

	digs = "0123456789abcdef";
	if (upper)
		digs = "0123456789ABCDEF";
	if (n == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return (1);
	}
	len = 0;
	while (n > 0)
	{
		tmp[len++] = digs[n % base];
		n /= base;
	}
	i = 0;
	while (i < len)
	{
		buf[i] = tmp[len - 1 - i];
		i++;
	}
	buf[len] = '\0';
	return (len);
}

void	ft_print_num(const char *pfx, char *dig, int dlen,
			t_format *f, int *count)
{
	int	plen;
	int	prec_zeros;
	int	total;
	int	wpad;

	plen = ft_mystrlen(pfx);
	prec_zeros = 0;
	if (f->precision >= 0 && f->precision > dlen)
		prec_zeros = f->precision - dlen;
	total = plen + prec_zeros + dlen;
	wpad = 0;
	if (f->width > total)
		wpad = f->width - total;
	if (!f->left_align && !(f->zero_pad && f->precision == -1))
		ft_putpad(wpad, ' ', count);
	ft_putmem_count(pfx, plen, count);
	if (!f->left_align && f->zero_pad && f->precision == -1)
		ft_putpad(wpad, '0', count);
	ft_putpad(prec_zeros, '0', count);
	ft_putmem_count(dig, dlen, count);
	if (f->left_align)
		ft_putpad(wpad, ' ', count);
}
