/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_convert(char spec, va_list args, int *count)
{
	if (spec == 'c')
		ft_putchar_count((char)va_arg(args, int), count);
	else if (spec == 's')
		ft_putstr_count(va_arg(args, char *), count);
	else if (spec == 'd' || spec == 'i')
		ft_putnbr_count(va_arg(args, int), count);
	else if (spec == 'u')
		ft_putunbr_count(va_arg(args, unsigned int), 10, 0, count);
	else if (spec == 'x')
		ft_putunbr_count(va_arg(args, unsigned int), 16, 0, count);
	else if (spec == 'X')
		ft_putunbr_count(va_arg(args, unsigned int), 16, 1, count);
	else if (spec == 'p')
		ft_putptr_count(va_arg(args, void *), count);
	else if (spec == '%')
		ft_putchar_count('%', count);
}

static void	ft_process_fmt(const char *fmt, va_list args, int *count)
{
	int	i;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			ft_convert(fmt[i + 1], args, count);
			i += 2;
		}
		else
		{
			ft_putchar_count(fmt[i], count);
			i++;
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
	ft_process_fmt(format, args, &count);
	va_end(args);
	return (count);
}
