/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 23:58:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 20:22:37 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include "keycode_mac.h"
# include "colors.h"
# include <stdarg.h>
# include <stdio.h>//

# define TITLE			"PRINTF"

typedef struct	s_buffer
{
	char		*buffer;
	size_t		size;
	size_t		pos;
	size_t		total;
	int			fd;
}				t_buffer;



typedef struct	s_lmod
{
	int		hh;
	int		h;
	int		ll;
	int		l;
	int		j;
	int		z;
}				t_lmod;

typedef struct	s_flags
{
	int		width;
	int		sharp;
	int		pad;
	char	padchar;
	int		precision;
	int		zero;
	int		minus;
	int		plus_sign;
	int		space;
}				t_flags;

typedef struct	s_args
{
	char		*s;
	char		c;
	wchar_t		*ws;
	wchar_t		wc;
	intmax_t	nb;
	uintmax_t	u_nb;
	void		*ptr;
}				t_args;
/*
 ** s1 is the string given by the user amd i current position
 ** s2 the string displayed
 */
typedef struct	s_input
{
	const char	*s1;
	int			i;
	char		tmp;
	char		s2;

	va_list		args;
	int			pc;
	t_args		targs;
	t_flags		flags;
	t_lmod		lmod;
}				t_input;
/*
 ** main program
 */

int		ft_printf(const char *restrict format, ...);
int		parsing_loop(const char **restrict format, va_list args);
int		parsing(t_input *input, char **s);
int		parse_param(t_input	input);
int		parse_flags(t_input	input);
int		parse_width(t_input	input);
int		parse_precision(t_input	input);
int		parse_length_modifier(t_input	input);
int		parse_type_conversion(t_input	input);
/*     
 ** Parsing functions
 */


#endif
