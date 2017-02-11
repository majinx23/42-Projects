/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:03:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/11 00:55:21 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	itoa_core(uintmax_t tmp, int base, char *str, t_flags *flags)
{
	int size;

	size = flags->printed;
	str[size] = '\0';
	while (--size >= 0)
	{
		str[size] = (tmp % base) + ((tmp % base >= 10) ? 87 - UPPER : '0');
		tmp /= base;
	}
}

char	*itoa_printf(intmax_t d, t_flags *flags)
{
	uintmax_t	tmp;
	char		*str;
	int			len;

	len = 0;
	tmp = (d < 0) ? -d : d;
	while (tmp && tmp /= 10)
		++len;
	(flags->a_zero) ? flags->precision = flags->min_length : 0;
	if ((d < 0 || flags->a_plus || flags->a_space) && flags->a_zero)
		flags->precision--;
	flags->printed = bigest(len, flags->precision);
	if (d < 0 || flags->a_plus || flags->a_space)
		flags->printed++;
	str = (char*)malloc(sizeof(char) * (flags->printed + 1));
	tmp = (d < 0) ? -d : d;
	itoa_core(tmp, 10, str, flags);
	(flags->a_plus) ? str[0] = '+' : 0;
	(flags->a_space) ? str[0] = ' ' : 0;
	(d < 0) ? str[0] = '-' : 0;
	return (str);
}

int		number(va_list ap, t_flags *flags)
{
	int			nb_spaces;
	char		*number;
	intmax_t	d;

	if (flags->l_long == 1)
		d = ((intmax_t)va_arg(ap, long));
	else if (flags->l_long == 2)
		d = ((intmax_t)va_arg(ap, long long));
	else if (flags->l_short == 1)
		d = (intmax_t)((short)va_arg(ap, int));
	else if (flags->l_short == 2)
		d = (intmax_t)((char)va_arg(ap, int));
	else if (flags->l_intmax)
		d = (va_arg(ap, intmax_t));
	else if (flags->l_sizet)
		d = ((intmax_t)va_arg(ap, ssize_t));
	else
		d = ((intmax_t)va_arg(ap, int));
	number = itoa_printf(d, flags);
	nb_spaces = flags->min_length - smallest(flags->printed, flags->min_length);
	adjust_length(nb_spaces, !flags->a_minus, ' ');
	ft_putstr(number);
	adjust_length(nb_spaces, flags->a_minus, ' ');
	return (bigest(flags->printed, flags->min_length));
}
