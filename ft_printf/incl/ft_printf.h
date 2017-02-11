/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 18:37:46 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/11 01:01:35 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define LONG			flags->l_long
# define TOTAL 			flags->total
# define UPPER			(32 * flags->uppercase)
# define COLOR(s,n)		ft_putstr(s), (format += n)
# define MAX(a, b)		b & ((a - b) >> 31) | a & (~(a - b) >> 31);
# define MIN(a, b)		a & ((a - b) >> 31) | b & (~(a - b) >> 31);
# define MSG_DIE(a,c,b)	ft_putstr(a), ft_putchar(c), ft_putendl(b), exit(TOTAL)

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <locale.h>
# include <errno.h>
# include <string.h>

typedef struct	s_flags
{
	int total;
	int printed;

	int prefix;
	int a_zero;
	int a_minus;
	int a_plus;
	int a_space;

	int min_length;
	int precision;

	int l_long;
	int l_short;
	int l_intmax;
	int l_sizet;

	int uppercase;
	int apply_precision;
}				t_flags;

int				ft_printf(char *format, ...);
char			*percent(char *format, va_list ap, t_flags *flags);
void			new_flags(t_flags *flags);

char			*search_flags(char *format, t_flags *flags);
char			*attributes(char *format, t_flags *flags);
char			*field_width(char *format, t_flags *flags);
char			*precision(char *format, t_flags *flags);
char			*length_modifier(char *format, t_flags *flags);

void			adjust_length(int nb_spaces, int on, char c);
int				bigest(int a, int b);
int				smallest(int a, int b);
char			*color(char *format, t_flags *flags);
void			stock_total(va_list ap, int total);

int				nbr_base(int base, va_list ap, t_flags *flags);
int				adress(va_list ap, t_flags *flags);
char			*itoa_base_printf(uintmax_t d, int b, t_flags *flags);

int				number(va_list ap, t_flags *flags);
void			itoa_core(uintmax_t tmp, int base, char *str, t_flags *flags);
char			*itoa_printf(intmax_t d, t_flags *flags);

int				string(va_list ap, t_flags *flags);
int				m_error(void);

int				character(va_list ap, t_flags *flags);
int				percent_char(t_flags *flags);
int				ft_putwchar(unsigned wchar);
#endif
