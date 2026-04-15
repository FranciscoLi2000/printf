/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_init_fmt(t_format *f)
{
	f->left_align = 0;
	f->zero_pad = 0;
	f->hash = 0;
	f->space = 0;
	f->width = 0;
	f->precision = -1;
	f->specifier = 0;
}

static void	ft_parse_flags(const char **fmt, t_format *f)
{
	while (**fmt == '-' || **fmt == '0' || **fmt == '#' || **fmt == ' ')
	{
		if (**fmt == '-')
			f->left_align = 1;
		else if (**fmt == '0')
			f->zero_pad = 1;
		else if (**fmt == '#')
			f->hash = 1;
		else
			f->space = 1;
		(*fmt)++;
	}
}

static void	ft_parse_width(const char **fmt, t_format *f)
{
	while (**fmt >= '0' && **fmt <= '9')
	{
		f->width = f->width * 10 + (**fmt - '0');
		(*fmt)++;
	}
}

static void	ft_parse_prec(const char **fmt, t_format *f)
{
	if (**fmt != '.')
		return ;
	(*fmt)++;
	f->precision = 0;
	while (**fmt >= '0' && **fmt <= '9')
	{
		f->precision = f->precision * 10 + (**fmt - '0');
		(*fmt)++;
	}
}

void	ft_parse_format(const char **fmt, t_format *f)
{
	ft_init_fmt(f);
	ft_parse_flags(fmt, f);
	ft_parse_width(fmt, f);
	ft_parse_prec(fmt, f);
	f->specifier = **fmt;
	if (**fmt)
		(*fmt)++;
}
