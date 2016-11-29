/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:53:26 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 16:24:28 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Reverses the chars in a string and returns the string.
*/

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		length;
	char	temp;
	int		i;

	i = 0;
	length = ft_strlen(str) - 1;
	if (length < 1)
		return (str);
	while (i < (length / 2 + 1))
	{
		temp = str[i];
		str[i] = str[length - i];
		str[length - i] = temp;
		i++;
	}
	return (str);
}
