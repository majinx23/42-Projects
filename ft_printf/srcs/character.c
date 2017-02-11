/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/11 01:03:25 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 00000000 -- 0000007F: 	0xxxxxxx
** 00000080 -- 000007FF: 	110xxxxx 10xxxxxx
** 00000800 -- 0000FFFF: 	1110xxxx 10xxxxxx 10xxxxxx
** 00010000 -- 001FFFFF: 	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

int			ft_putwchar(unsigned wchar)
{
	int nb_bytes;

	nb_bytes = wcharlen(wchar);
	if (nb_bytes == 1)
		ft_putchar(wchar);
	else if (nb_bytes == 2)
	{
		ft_putchar(((wchar & (0x1f << 6)) >> 6) + 0xC0);
		ft_putchar(((wchar & 0x3f)) + 0x80);
	}
	else if (nb_bytes == 3)
	{
		ft_putchar(((wchar & (0xf << 12)) >> 12) + 0xE0);
		ft_putchar(((wchar & (0x3f << 6)) >> 6) + 0x80);
		ft_putchar(((wchar & 0x3f)) + 0x80);
	}
	else
	{
		ft_putchar(((wchar & (0x7 << 18)) >> 18) + 0xF0);
		ft_putchar(((wchar & (0x3f << 12)) >> 12) + 0x80);
		ft_putchar(((wchar & (0x3f << 6)) >> 6) + 0x80);
		ft_putchar(((wchar & 0x3f)) + 0x80);
	}
	return (nb_bytes);
}

int			character(va_list ap, t_flags *flags)
{
	unsigned	c;
	int			charlen;

	c = va_arg(ap, unsigned);
	charlen = wcharlen(c);
	adjust_length(flags->min_length - charlen, !flags->a_minus, ' ');
	ft_putwchar(c);
	adjust_length(flags->min_length - charlen, flags->a_minus, ' ');
	return (bigest(flags->min_length, charlen));
}

int			percent_char(t_flags *flags)
{
	adjust_length(flags->min_length - 1, !flags->a_minus,
			((flags->a_zero) ? '0' : ' '));
	ft_putwchar('%');
	adjust_length(flags->min_length - 1, flags->a_minus, ' ');
	return (bigest(flags->min_length, 1));
}
