/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:50:25 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 14:58:30 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates and returns a null-terminated character string representing the
** integer n. Negative numbers are also considered.
** If memory allocation fails, return NULL.
*/

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		count;

	nb = n;
	count = (nb <= 0) ? 1 : 0;
	while (n && ++count)
		n /= 10;
	if (!(str = (char *)malloc(sizeof(char) * count + 1)))
		return (NULL);
	str[0] = (nb < 0) ? '-' : '0';
	nb = (nb < 0) ? -nb : nb;
	str[count] = '\0';
	while (nb)
	{
		str[--count] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
