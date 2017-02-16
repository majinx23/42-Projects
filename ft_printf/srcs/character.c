/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/16 11:18:24 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

/*
** handles %%
*/

int		percent_char(t_printf *p)
{
	if (!p->flags.min && p->min_length - 1 > 0)
		ft_putnchar(p->min_length - 1, (p->flags.zero) ? '0' : ' ');
	ft_putwchar('%', 4);
	if (p->flags.min)
		ft_putnchar(p->min_length, ' ');
	return (MAX(p->min_length, 1));
}

/*
** returns a single character len and display it
** refer to libft for putwchar amd wcharlen functions
*/

void	pf_character(va_list ap, t_printf *p)
{
	unsigned	c;
	int			len;

	c = va_arg(ap, unsigned);
	len = (p->lm.llong) ? ft_wcharlen(c) : 1;
//	ft_putnbr(p->flags.zero);
	if (!p->flags.min)
		ft_putnchar(p->min_length - MIN(len, p->min_length), (p->flags.zero) ? '0' : ' ');
	(p->lm.llong) ? ft_putwchar(c, 4) : ft_putchar(c);
	if (p->flags.min)
		ft_putnchar(p->min_length - MIN(len, p->min_length), ' ');
	p->len += MAX(p->min_length, len);
}

/*
** write a single regular character and adds 1 to p->len
*/

void	pf_putchar(char c, t_printf *p)
{
	write(1, &c, 1);
	++p->len;
}

int		print_pointer_address(va_list ap, t_printf *p)
{
	int				sp_padding;
	char			*s;
	void			*pointer;

	p->flags.sharp = 0;
	pointer = va_arg(ap, void *);
	s = itoa_base_printf((uintmax_t)pointer, 16, p);
	sp_padding = (p->printed > p->min_length - 2) ? 0 : p->min_length - 2 - p->printed;

//	sp_padding = p->min_length - MIN(p->printed + 2, p->min_length);
	if (!p->flags.min)
		ft_putnchar(sp_padding, ((p->flags.zero) ? '0' : ' '));
	ft_putstr("0x");
	ft_putstr(s);
	if (p->flags.min)
		ft_putnchar(sp_padding, ((p->flags.zero) ? '0' : ' '));
	return (MAX(p->printed + 2, p->min_length));
}
