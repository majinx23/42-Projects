/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:03:26 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 20:03:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pointer(va_list ap, t_flags *flags)
{
	void	*point;

	point = va_arg(ap, void*);
	(void)flags;
	ft_putstr("0x............");
	return ;
}
