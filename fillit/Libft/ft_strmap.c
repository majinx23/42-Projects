/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:44:03 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:43:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies the function f to each character in the string s to create a new
** string with the return values of f.
** Returns the new string.
*/

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*s2;
	int		i;

	if (!s)
		return (NULL);
	s2 = (char *)s;
	i = 0;
	if (!(str = ft_strnew(ft_strlen(s2))))
		return (0);
	while (s2[i])
	{
		str[i] = (*f)(s2[i]);
		i++;
	}
	return (str);
}
