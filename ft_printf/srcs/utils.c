/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:16 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 19:22:11 by angavrel         ###   ########.fr       */
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

char	*color(char *format)
{
	if (!ft_strncmp(format,"{red}", 5))
		ft_putstr("\033[31m"), (format += 5);
	else if (!ft_strncmp(format,"{yellow}", 8))
		ft_putstr("\033[33m"), (format += 8);
	else if (!ft_strncmp(format,"{green}", 7))
		ft_putstr("\033[32m"), (format += 7);
	else if (!ft_strncmp(format,"{cyan}", 6))
		ft_putstr("\033[36m"), (format += 6);
	else if (!ft_strncmp(format,"{blue}", 6))
		ft_putstr("\033[34m"), (format += 6);
	else if (!ft_strncmp(format,"{purple}", 8))
		ft_putstr("\033[35m"), (format += 8);
	else if (!ft_strncmp(format,"{eoc}", 5))
		ft_putstr("\033[37m"), (format += 5);
	return (format - 1);
}

/*
char	*print_color(char *format, char *color_str, int length)
{
	ft_putstr(color_str)
	return (format + length - 1);
}*/
