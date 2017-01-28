/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:16:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 20:22:08 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//l'attribut - calcule pour toute conversion, grace a min_length

char	*search_flags(char *format, t_flags *flags)
{
	format = attributes(format, flags);
	format = field_width(format, flags);
	format = precision(format, flags);
	format = length_modifier(format, flags);
	return (format);
}



void	print_flags(t_flags *flags)
{
	printf("#: %d\n0: %d\n+: %d\n-: %d\n : %d\n\nmin_length: %d\nprecision: %d\n\nlong:   %d\nshort:  %d\nintmax: %d\nsize_t: %d\n",
		  flags->a_sharp,flags->a_zero,flags->a_plus,flags->a_minus,flags->a_space,
		  flags->min_length,flags->precision,
		  flags->l_long,flags->l_short,flags->l_intmax,flags->l_sizet);
	return ;
}

char	*attributes(char *format, t_flags *flags)
{
	while (ft_strchr("#0+- ", *format))
	{
		(*format == '#') ? flags->a_sharp = 1 : 0;
		(*format == '0') ? flags->a_zero  = 1 : 0;
		(*format == '+') ? flags->a_plus  = 1 : 0;
		(*format == '-') ? flags->a_minus = 1 : 0;
		(*format == ' ') ? flags->a_space = 1 : 0;
		format++;
	}
	(flags->a_minus) ? flags->a_zero = 0 : 0;
	(flags->a_plus) ? flags->a_space = 0 : 0;
	return(format);
}

char	*field_width(char *format, t_flags *flags)
{
	long value;

	if (ft_strchr("123456789", *format))
	{
		value = ft_atoi(format);//recoder noter atoi en brut ici pour eviter un probleme ?
		if (value < 0) // c'est cense ne jamais arriver, sauf si atoi retourne un nombre indefini :(
		{
			value = (-value);
			flags->a_minus = 1; //penser a surcharger '0' ???
		}
		flags->min_length = value;
		while(ft_strchr("0123456789", *format))
			format++;
	}
	return(format);
}

char	*precision(char *format, t_flags *flags)
{
	int value;

	if (ft_strchr(".", *format))
	{
		value = ft_atoi(++format);//devrait passer
		flags->precision = (value > 0) ? value : 0;
		while(ft_strchr("0123456789", *format))
			format++;
		flags->apply_precision = 1;
	}
	return(format);
}

char	*length_modifier(char *format, t_flags *flags)
{
	while (ft_strchr("hljz", *format))
	{
		(*format == 'h') ? flags->l_short  = 1 : 0;
		(*format == 'l') ? flags->l_long   = 1 : 0;
		(*format == 'j') ? flags->l_intmax = 1 : 0;
		(*format == 'z') ? flags->l_sizet  = 1 : 0;
		format++;
	}
	return(format);
}

