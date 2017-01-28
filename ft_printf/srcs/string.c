/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 19:31:22 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 18:56:33 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	string(va_list ap, t_flags *flags)
{
	char	*str;
	int		nb_spaces;
	str = va_arg(ap, char*);

	if (!flags->apply_precision)
		flags->precision = ft_strlen(str);
	nb_spaces = flags->min_length - ((flags->precision < (int)ft_strlen(str)) ? flags->precision : ft_strlen(str));
	adjust_length(nb_spaces, !flags->a_minus);
	while (*str && flags->precision)
	{
			ft_putchar(*str);
		flags->precision--;
		str++;
	}
	adjust_length(nb_spaces, flags->a_minus);
	return ;
}
