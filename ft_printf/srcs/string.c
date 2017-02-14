/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 19:31:22 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/14 10:17:43 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

/*
** print wide string and returns total len
** please refer to libft for ft_wcharlen and ft_wstrlen
*/

int		pf_wide_string(va_list ap, t_printf *p)
{
	wchar_t		*s;
	int			wlen;
	int			sp_padding;

	if ((s = va_arg(ap, wchar_t *)) && !s)
		return (ft_printf_putwstr((wchar_t *)s));
	wlen = (int)(ft_wstrlen((unsigned *)s));
	(p->apply_precision) ? wlen = MIN(p->precision, wlen) : 0;
	sp_padding = p->min_length - MIN(p->precision, wlen);
//	if (!p->flags.min)
//		ft_putnchar(sp_padding, ' ');		
	while (*s && wlen--)
	{
		p->printed += ft_putwchar(*s);
		++s;
	}
	if (p->flags.min)
		ft_putnchar(sp_padding, ' ');
	return (p->printed + MAX(sp_padding, 0));
}

/*
** print regular string and returns its len
*/

int		pf_string(va_list ap, t_printf *p)
{
	unsigned	*s;
	int			len;
	int			sp_padding;
	
	if (!(s = va_arg(ap, unsigned*)))
		return (ft_printf_putstr((char *)s, p));
	len = (int)(ft_strlen((char*)s));
	(p->apply_precision) ? len = MIN(p->precision, len) : 0;
	sp_padding = (p->min_length - len) > 0 ? (p->min_length - len) : 0;
//	ft_putnchar(sp_padding, ' ');


//	ft_putnbr(sp_padding);
//	ft_putnbr(p->min_length);
//	ft_putnbr(len);
	//	sp_padding = MIN(p->precision - len, len);
	if (!p->flags.min)
		ft_putnchar(sp_padding, (p->flags.zero) ? '0' : ' ');
	while ((char)*s && len--)
	{
		ft_putchar((char)(*s));
		++p->printed;
		s = (unsigned *)((char*)s + 1);
	}
	if (p->flags.min)
		ft_putnchar(sp_padding, ' ');
	p->printed += MAX(sp_padding, 0);
	return (p->printed);
}

/*
** prints string and returns its len, if no len will print (null) and return 6
*/

int		ft_printf_putstr(char *s, t_printf *p)
{
	if (!s)
	{
		(!p->flags.zero) ? ft_putstr("(null)") : ft_putnchar(p->min_length, '0');
		return ((!p->flags.zero) ? 6 : p->min_length);
	}
	ft_putstr(s);
	return ((int)ft_strlen(s));
}

int		ft_printf_putwstr(wchar_t *s)
{
	(!s) ? ft_putstr("(null)") : ft_putwstr(s);
	return (!s ? 6 : (int)ft_wstrlen((unsigned *)s));
}
