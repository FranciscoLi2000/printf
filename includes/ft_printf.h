#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
void	ft_putchar(char c, int *count);
void	ft_putstr(char *s, int *count);
void	ft_putnbr(int nbr, int *count);
void	ft_putnbr_base(unsigned int nbr, char *base, int *count);
void	ft_putptr(void *ptr, int *count);
int	parse_format(const char **format, va_list ap, int *count);

#endif
