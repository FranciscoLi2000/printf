/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_format
{
	int		left_align;
	int		zero_pad;
	int		hash;
	int		space;
	int		width;
	int		precision;
	char	specifier;
}	t_format;

/* Main function */
int		ft_printf(const char *format, ...);

/* Parse */
void	ft_init_fmt(t_format *f);
void	ft_parse_format(const char **fmt, t_format *f);

/* Utilities */
void	ft_putchar_count(char c, int *count);
void	ft_putpad(int n, char c, int *count);
void	ft_putmem_count(const char *s, int n, int *count);
int		ft_mystrlen(const char *s);
int		ft_uitoa_base(unsigned long n, unsigned int base,
			int upper, char *buf);
void	ft_print_num(const char *pfx, char *dig, int dlen,
			t_format *f, int *count);

/* Char and string */
void	ft_putchar_bonus(t_format *f, int c, int *count);
void	ft_putstr_bonus(t_format *f, char *s, int *count);

/* Numbers */
void	ft_putnbr_bonus(t_format *f, int n, int *count);

/* Hex and pointer */
void	ft_putu_bonus(t_format *f, unsigned int n, int *count);
void	ft_puthex_bonus(t_format *f, unsigned int n, int upper,
			int *count);
void	ft_putptr_bonus(t_format *f, void *ptr, int *count);

#endif
