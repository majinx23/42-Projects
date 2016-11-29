/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:15:19 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 14:45:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts the initial portion of the string pointed to by str to int
** representation. Ignores ht, nl, vt, np (new page), cr (carriage return)
** and space.
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	long			result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 9 || str[i] == 10 ||
			str[i] == 11 || str[i] == 12 ||
			str[i] == 13 || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return ((int)(sign * result));
}
