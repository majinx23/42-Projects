/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 19:31:22 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/13 12:09:32 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

/*
** print wide string and returns total len
** please refer to libft for ft_wcharlen and ft_wstrlen
*/

int		wide_string(va_list ap, t_printf *p)
{
	unsigned	*s;
	int			wlen;
	int			sp_padding;

	if ((s = va_arg(ap, unsigned*)) && !s)
		return (ft_printf_putwstr((wchar_t *)s));
	wlen = (int)(ft_wstrlen(s));
	if (!p->apply_precision)
		p->precision = wlen;

	
	sp_padding = p->min_length - MIN(p->precision, wlen);
//	if (!p->flags.min)
//		ft_putnchar(sp_padding, ' ');
			
	while ((wchar_t)*s && p->precision >= (int)ft_wcharlen(*s))
	{
		ft_putwchar(*s);
		p->precision -= ft_wcharlen(*s);
		p->printed += ft_wcharlen(*s);
		++s;
	}
	if (p->flags.min)
		ft_putnchar(sp_padding, ' ');
	return (p->printed + MAX(sp_padding, 0));
}

/*
** print regular string and returns its len
*/

int		string(va_list ap, t_printf *p)
{
	unsigned	*s;
	int			len;
	int			sp_padding;
	
	if (!(s = va_arg(ap, unsigned*)))
		return (ft_printf_putstr((char *)s));
	len = (int)(ft_strlen((char*)s));
	if (!p->apply_precision)
		p->precision = len;
	sp_padding = p->min_length - MIN(p->precision, len);
//	if (!p->flags.min)
//		ft_putnchar(sp_padding, ' ');
	while ((char)*s && p->precision >= 1)
	{
		ft_putchar((char)(*s));
		--p->precision;
		++p->printed;
		s = (unsigned *)((char*)s + 1);
	}
	if (p->flags.min)
		ft_putnchar(sp_padding, ' ');
	return (p->printed + MAX(sp_padding, 0));
}

/*
** prints string and returns its len, if no len will print (null) and return 6
*/

int		ft_printf_putstr(char *s)
{
	(!s) ? ft_putstr("(null)") : ft_putstr(s);
	return (!s ? 6 : (int)ft_strlen(s));
}

int		ft_printf_putwstr(wchar_t *s)
{
	(!s) ? ft_putstr("(null)") : ft_putwstr(s);
	return (!s ? 6 : (int)ft_wstrlen((unsigned *)s));
}
