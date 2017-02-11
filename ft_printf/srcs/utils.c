/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:16 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/11 01:02:24 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	adjust_length(int nb_spaces, int on)
{
	while (nb_spaces > 0 && on)
	{
		ft_putchar(' ');
		nb_spaces--;
	}
	return ;
}

char	*color(char *format, t_flags *flags)
{
	flags->printed = 5;
	if (!ft_strncmp(format, "{red}", 5))
		COLOR("\033[31m", 5);
	else if (!ft_strncmp(format, "{yellow}", 8))
		COLOR("\033[33m", 8);
	else if (!ft_strncmp(format, "{green}", 7))
		COLOR("\033[32m", 7);
	else if (!ft_strncmp(format, "{cyan}", 6))
		COLOR("\033[36m", 6);
	else if (!ft_strncmp(format, "{blue}", 6))
		COLOR("\033[34m", 6);
	else if (!ft_strncmp(format, "{purple}", 8))
		COLOR("\033[35m", 8);
	else if (!ft_strncmp(format, "{eoc}", 5))
		COLOR("\033[37m", 5);
	else
		flags->printed = 0;
	flags->total += flags->printed;
	return (format - 1);
}

void	stock_total(va_list ap, int total)
{
	int *pointer;

	pointer = va_arg(ap, int *);
	*pointer = total;
	return ;
}
