/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:16:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/11 00:07:40 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*search_flags(char *format, t_flags *flags)
{
	format = attributes(format, flags);
	format = field_width(format, flags);
	format = precision(format, flags);
	format = length_modifier(format, flags);
	return (format);
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
	return (format);
}

char	*field_width(char *format, t_flags *flags)
{
	if (ft_strchr("123456789", *format))
	{
		flags->min_length = ft_atoi(format);
		while (ft_strchr("0123456789", *format))
			format++;
	}
	return (format);
}

char	*precision(char *format, t_flags *flags)
{
	int value;

	if (ft_strchr(".", *format))
	{
		value = ft_atoi(++format);
		flags->precision = (value > 0) ? value : 0;
		while (ft_strchr("0123456789", *format))
			format++;
		flags->apply_precision = 1;
		flags->a_zero = 0;
	}
	return (format);
}

char	*length_modifier(char *format, t_flags *flags)
{
	while (ft_strchr("hljz", *format))
	{
		if (*format == 'h')
		{
			flags->l_short = 1;
			if (*(format + 1) == 'h')
			{
				flags->l_short = 2;
				format++;
			}
		}
		if (*format == 'l')
		{
			flags->l_long = 1;
			if (*(format + 1) == 'l')
			{
				flags->l_long = 2;
				format++;
			}
		}
		(*format == 'j') ? flags->l_intmax = 1 : 0;
		(*format == 'z') ? flags->l_sizet = 1 : 0;
		format++;
	}
	return (format);
}
