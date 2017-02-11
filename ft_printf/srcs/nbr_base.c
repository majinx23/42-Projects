/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:03:38 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/11 01:29:29 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_base_printf(uintmax_t d, int b, t_flags *flags)
{
	uintmax_t	tmp;
	char		*s;
	int			len;
	int			extend;

	len = 0;
	tmp = d;
	while (tmp && tmp /= b)
		++len;
	(flags->a_zero) ? flags->precision = flags->min_length : 0;
	extend = (len >= flags->precision) ? 0 : 1;
	(flags->prefix && b == 8 && !extend) ? flags->precision -= 1 : 0;
	(flags->prefix && b == 16 && d) ? flags->precision -= 2 : 0;
	flags->printed = bigest(len, flags->precision);
	(flags->prefix && b == 8 && !extend) ? flags->printed += 1 : 0;
	(flags->prefix && b == 16 && d) ? flags->printed += 2 : 0;
	str = (char*)malloc(sizeof(char) * (flags->printed + 1));
	itoa_core(d, b, str, flags);
	(flags->prefix && b == 8 && !extend) ? str[0] = '0' : 0;
	(flags->prefix && b == 16 && d) ? str[0] = '0' : 0;
	(flags->prefix && b == 16 && d) ? str[1] = 'x' - UPPER : 0;
	return (str);
}

int		nbr_base(int base, va_list ap, t_flags *flags)
{
	int			nb_spaces;
	char		*number;
	uintmax_t	d;

	if (flags->l_long == 1)
		d = ((uintmax_t)va_arg(ap, unsigned long));
	else if (flags->l_long == 2)
		d = ((uintmax_t)va_arg(ap, unsigned long long));
	else if (flags->l_short == 1)
		d = (uintmax_t)((unsigned short)va_arg(ap, int));
	else if (flags->l_short == 2)
		d = (uintmax_t)((unsigned char)va_arg(ap, int));
	else if (flags->l_intmax)
		d = (va_arg(ap, uintmax_t));
	else if (flags->l_sizet)
		d = ((uintmax_t)va_arg(ap, size_t));
	else
		d = (uintmax_t)va_arg(ap, unsigned int);
	number = itoa_base_printf(d, base, flags);
	nb_spaces = flags->min_length - smallest(flags->printed, flags->min_length);
	adjust_length(nb_spaces, !flags->a_minus, ' ');
	ft_putstr(number);
	adjust_length(nb_spaces, flags->a_minus, ' ');
	return (bigest(flags->printed, flags->min_length));
}

int		adress(va_list ap, t_flags *flags)
{
	int				nb_spaces;
	char			*number;
	void			*point;

	flags->prefix = 0;
	point = va_arg(ap, void *);
	number = itoa_base_printf((uintmax_t)point, 16, flags);
	nb_spaces = flags->min_length -
		smallest(flags->printed + 2, flags->min_length);
	adjust_length(nb_spaces, !flags->a_minus, ((flags->a_zero) ? '0' : ' '));
	ft_putstr("0x");
	ft_putstr(number);
	adjust_length(nb_spaces, flags->a_minus, ' ');
	return (bigest(flags->printed + 2, flags->min_length));
}
