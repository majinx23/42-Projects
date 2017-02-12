/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:03:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/12 09:35:38 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		p_putnb(va_list ap, t_printf *p)
{
	char		*s;
	intmax_t	n;
	int			sp_padding;

	if (p->lm.llong)
		n = (p->lm.llong >> 1) ? ((intmax_t)va_arg(ap, long long)) :
			((intmax_t)va_arg(ap, long));
	else if (p->lm.sshort)
		n = (p->lm.sshort >> 1) ? (intmax_t)((char)va_arg(ap, int)) :
			(intmax_t)((short)va_arg(ap, int));
	else if (p->lm.intmax)
		n = (va_arg(ap, intmax_t));
	else if (p->lm.sizet)
		n = ((intmax_t)va_arg(ap, ssize_t));
	else
		n = ((intmax_t)va_arg(ap, int));
	if (p->flags.zero)
		p->precision = p->min_length;
	s = itoa_printf(n, p);
	sp_padding = p->min_length - MIN(p->printed, p->min_length);
	!p->flags.min ? ft_putnchar(sp_padding, ' ') : 0;
	ft_putstr(s);
	p->flags.min ? ft_putnchar(sp_padding, ' ') : 0;
	return (MAX(p->printed, p->min_length));
}

int		p_putnb_base(int base, va_list ap, t_printf *p)
{
	char		*s;
	uintmax_t	n;
	int			sp_padding;

	if (p->lm.llong)
		n = (p->lm.llong >> 1) ? ((intmax_t)va_arg(ap, unsigned long long)) :
			((intmax_t)va_arg(ap, unsigned long));
	else if (p->lm.sshort)
		n = (p->lm.sshort >> 1) ? (uintmax_t)((unsigned char)va_arg(ap, int)) :
			(uintmax_t)((unsigned short)va_arg(ap, int));
	else if (p->lm.intmax)
		n = (va_arg(ap, uintmax_t));
	else if (p->lm.sizet)
		n = ((intmax_t)va_arg(ap, ssize_t));
	else if (p->lm.intmax)
		n = (va_arg(ap, uintmax_t));
	else if (p->lm.sizet)
		n = ((uintmax_t)va_arg(ap, size_t));
	else
		n = (uintmax_t)va_arg(ap, unsigned int);
	s = itoa_base_printf(n, base, p);
	sp_padding = p->min_length - MIN(p->printed, p->min_length);
	!p->flags.min ? ft_putnchar(sp_padding, ' ') : 0;
	ft_putstr(s);
	p->flags.min ? ft_putnchar(sp_padding, ' ') : 0;
	return (MAX(p->printed, p->min_length));
}

char	*itoa_printf(intmax_t n, t_printf *p)
{
	char		*s;
	int			len;
	uintmax_t	tmp;

	len = 0;
	tmp = (n < 0) ? -n : n;
	while (tmp && (tmp /= 10))
		++len;
	if ((n < 0 || p->flags.plus || p->flags.sp) && p->flags.zero)
		--p->precision;
	p->printed = MAX(len, p->precision);
	if (n < 0 || p->flags.plus || p->flags.sp)
		++p->printed;
	if (!(s = (char*)malloc(sizeof(char) * (p->printed + 1))))
		return (NULL);
	tmp = (n < 0) ? -n : n;
	itoa_core(n, 10, s, p);
	(p->flags.plus) ? s[0] = '+' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->flags.sp) ? s[0] = ' ' : 0;
	return (s);
}

char	*itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	uintmax_t	tmp;
	char		*s;
	int			len;
	int			extend;

	len = 0;
	tmp = n;
	while (tmp && (tmp /= b))
		++len;
	(p->flags.zero) ? p->precision = p->min_length : 0;
	extend = (len >= p->precision) ? 0 : 1;
	(p->flags.sharp && b == 8 && !extend) ? --p->precision : 0;
	(p->flags.sharp && b == 16 && n) ? p->precision -= 2 : 0;
	p->printed = MAX(p->precision, len);
	(p->flags.sharp && b == 8 && !extend) ? p->printed += 1 : 0;
	(p->flags.sharp && b == 16 && n) ? p->printed += 2 : 0;
	if (!(s = (char*)malloc(sizeof(char) * (p->printed + 1))))
		return (NULL);
	itoa_core(n, b, s, p);
	(p->flags.sharp && b == 8 && !extend) ? s[0] = '0' : 0;
	(p->flags.sharp && b == 16 && n) ? s[0] = '0' : 0;
	(p->flags.sharp && b == 16 && n) ? s[1] = 'x' - p->cs.upcase * 32 : 0;
	return (s);
}

/*
** variable letter only works for base 16 in printf
*/

void	itoa_core(uintmax_t tmp, int b, char *s, t_printf *p)
{
	int		letter;
	int		len;

	len = p->printed;
	letter = 'a' - 10 - (p->cs.upcase * 32);
	s[len] = '\0';
	while (len--)
	{
		s[len] = tmp % 10 + ((tmp % b < 10) ? '0' : letter);
		tmp /= 10;
	}
}
