/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 18:37:46 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 20:39:53 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h> //printf

/*
** stdarg is for variadic functions, stdlib for malloc free and exit,
** unistd for write, wchar for %lc and locale to define the locale for wchars
*/

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <locale.h>
# include <wchar.h>

typedef struct s_flags
{
	int printed;

	int a_sharp;
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
}		t_flags;



void	msg_die(char *message);

int		ft_printf(const char *restrict format, ...);
char	*percent(char *format, va_list ap, int *flag_len);
void	new_flags(t_flags *flags);
void	print_flags(t_flags *flags);
char	*color(char *format);

char	*search_flags(char *format, t_flags *flags);
char	*attributes(char *format, t_flags *flags);
char	*field_width(char *format, t_flags *flags);
char	*precision(char *format, t_flags *flags);
char	*length_modifier(char *format, t_flags *flags);

void	adjust_length(int nb_spaces, int on);


void	string(va_list ap, t_flags *flags);

int		number(va_list ap, t_flags *flags);
char	*itoa_printf(va_list ap, t_flags *flags);

void	pointer(va_list ap, t_flags *flags);

void	character(va_list ap, t_flags *flags);
int		ft_putwchar(unsigned wchar);

void	nbr_base(int base, va_list ap, t_flags *flags);
#endif
