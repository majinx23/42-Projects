/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 18:37:46 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/12 11:59:08 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MAX(a, b)			b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)			a & ((a - b) >> 31) | b & (~(a - b) >> 31)
# define COLOR(s,n)			ft_putstr(s), (format += n)

# include "../libft/libft.h"
# include <stdarg.h>
# include <locale.h>
# include <errno.h>

/*
** refer to parsing.c for description of variables in below structures
*/

typedef struct	s_flags
{
	int sharp;
	int zero;
	int min;
	int plus;
	int sp;
}				t_flags;

typedef	struct	s_length_modifier
{
	int sshort;
	int llong;
	int intmax;
	int sizet;
}				t_length_modifier;

typedef struct	s_conversion_specifier
{
	int upcase;
}				t_conversion_specifier;

typedef struct	s_printf
{
	int						len;
	t_flags					flags;
	int						min_length;
	int						precision;
	int						apply_precision;
	t_length_modifier		lm;
	t_conversion_specifier	cs;
	int						printed;
}				t_printf;

/*
** main program
*/

int				ft_printf(char *format, ...);
int				ft_printf_putchar(char c);

/*
** parsing optional parameters
*/

char			*parse_optionals(char *format, t_printf *p);
char			*parse_flags(char *format, t_flags *flags);
char			*field_width(char *format, t_printf *p);
char			*precision(char *format, t_printf *p);
char			*length_modifier(char *format, t_length_modifier *lm);

/*
** parsing conversion specifier
*/

char			*conversion_specifier(char *format, va_list ap, t_printf *p);
int				percent_char(t_printf *p);

int				p_putnb(va_list ap, t_printf *p);
int				p_putnb_base(int base, va_list ap, t_printf *p);
char			*itoa_printf(intmax_t d, t_printf *p);
char			*itoa_base_printf(uintmax_t d, int b, t_printf *p);
void			itoa_base_fill(uintmax_t tmp, int base, char *str, t_printf *p);

int				string(va_list ap, t_printf *p);
int				wide_string(va_list ap, t_printf *p);
int				character(va_list ap, t_printf *p);
int				ft_putwchar(unsigned wchar);
int				p_putchar(char c);

int				print_pointer_address(va_list ap, t_printf *p);
void			print_len(va_list ap, int len);
int				ft_printf_putstr(char *s);

void			ft_putnchar(int len, char c);
char			*color(char *format, t_printf *p);

#endif
