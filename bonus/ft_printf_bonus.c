/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_dispatch(t_format *f, va_list args, int *count)
{
	if (f->specifier == 'c')
		ft_putchar_bonus(f, va_arg(args, int), count);
	else if (f->specifier == 's')
		ft_putstr_bonus(f, va_arg(args, char *), count);
	else if (f->specifier == 'd' || f->specifier == 'i')
		ft_putnbr_bonus(f, va_arg(args, int), count);
	else if (f->specifier == 'u')
		ft_putu_bonus(f, va_arg(args, unsigned int), count);
	else if (f->specifier == 'x')
		ft_puthex_bonus(f, va_arg(args, unsigned int), 0, count);
	else if (f->specifier == 'X')
		ft_puthex_bonus(f, va_arg(args, unsigned int), 1, count);
	else if (f->specifier == 'p')
		ft_putptr_bonus(f, va_arg(args, void *), count);
	else if (f->specifier == '%')
		ft_putchar_count('%', count);
}

static void	ft_process_bonus(const char *fmt, va_list args, int *count)
{
	t_format	f;

	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			ft_parse_format(&fmt, &f);
			ft_dispatch(&f, args, count);
		}
		else
		{
			ft_putchar_count(*fmt, count);
			fmt++;
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	ft_process_bonus(format, args, &count);
	va_end(args);
	return (count);
}
