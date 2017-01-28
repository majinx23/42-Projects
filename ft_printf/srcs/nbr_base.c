/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:03:38 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 20:03:40 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void nbr_base(int base, va_list ap, t_flags *flags)
{
	int deci;

	deci = va_arg(ap, int);
	(void)flags;
	ft_putstr("{nbr_base ");
	ft_putnbr(base);
	ft_putstr("}");
	return ;
}
