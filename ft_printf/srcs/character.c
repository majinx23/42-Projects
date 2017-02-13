/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/13 12:03:33 by angavrel         ###   ########.fr       */
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
** refer to libft for putwchar amd wcharlen functions
*/

int		character(va_list ap, t_printf *p)
{
	unsigned	c;
	int			len;

	c = va_arg(ap, unsigned);
	len = ft_wcharlen(c);
	if (!p->flags.min)
		ft_putnchar(p->min_length - MIN(len, p->min_length), ' ');
	ft_putwchar(c);
	if (p->flags.min)
		ft_putnchar(p->min_length - MIN(len, p->min_length), ' ');
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

int		print_pointer_address(va_list ap, t_printf *p)
{
	int				sp_padding;
	char			*s;
	void			*pointer;

	p->flags.sharp = 0;
	pointer = va_arg(ap, void *);
	s = itoa_base_printf((uintmax_t)pointer, 16, p);
	sp_padding = p->min_length - MIN(p->printed + 2, p->min_length);
	if (!p->flags.min)
		ft_putnchar(sp_padding, ((p->flags.zero) ? '0' : ' '));
	ft_putstr("0x");
	ft_putstr(s);
	if (p->flags.min)
		ft_putnchar(sp_padding, ' ');
	return (MAX(p->printed + 2, p->min_length));
}
