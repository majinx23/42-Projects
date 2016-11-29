/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:56:38 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 19:20:38 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Locates the first occurence of the null-terminated string little in the
** null-terminated string big.
*/

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	l = ft_strlen(little);
	while (big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] && big[i + j] == little[j] && little[j])
			{
				j++;
			}
			if (j == l)
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
