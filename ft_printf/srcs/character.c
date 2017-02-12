/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/12 11:09:03 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

/*
** handles %%
*/

int		percent_char(t_printf *p)
{
	if (!p->flags.min)
		ft_putnchar(p->min_length, (p->flags.zero) ? '0' : ' ');
	ft_putwchar('%');
	if (p->flags.min)
		ft_putnchar(p->min_length, ' ');
	return (MAX(p->min_length, 1));
}

/*
** returns a single character len and display it
*/

int		character(va_list ap, t_printf *p)
{
	unsigned	c;
	int			len;

	c = va_arg(ap, unsigned);
	len = ft_wcharlen(c);
	if (!p->flags.min)
		ft_putnchar(p->min_length - len, ' ');
	ft_putwchar(c);
	if (p->flags.min)
		ft_putnchar(p->min_length - len, ' ');
	return (MAX(p->min_length, len));
}

/*
** write a single regular character and returns 1
*/

int		p_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

/*
** 00000000 -- 0000007F: 	0xxxxxxx
** 00000080 -- 000007FF: 	110xxxxx 10xxxxxx
** 00000800 -- 0000FFFF: 	1110xxxx 10xxxxxx 10xxxxxx
** 00010000 -- 001FFFFF: 	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

int		ft_putwchar(unsigned wc)
{
	int nb_bytes;

	nb_bytes = ft_wcharlen(wc);
	if (nb_bytes == 1)
		ft_putchar(wc);
	else if (nb_bytes == 2)
	{
		ft_putchar(((wc & (0x1f << 6)) >> 6) + 0xC0);
		ft_putchar(((wc & 0x3f)) + 0x80);
	}
	else if (nb_bytes == 3)
	{
		ft_putchar(((wc & (0xf << 12)) >> 12) + 0xE0);
		ft_putchar(((wc & (0x3f << 6)) >> 6) + 0x80);
		ft_putchar(((wc & 0x3f)) + 0x80);
	}
	else
	{
		ft_putchar(((wc & (0x7 << 18)) >> 18) + 0xF0);
		ft_putchar(((wc & (0x3f << 12)) >> 12) + 0x80);
		ft_putchar(((wc & (0x3f << 6)) >> 6) + 0x80);
		ft_putchar(((wc & 0x3f)) + 0x80);
	}
	return (nb_bytes);
}
