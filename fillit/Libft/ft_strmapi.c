/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:02:15 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:44:18 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies the function f to each character in the string s to create a new
** string with the return values of f. f takes the index of the char as well.
** Returns the new string.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	char			*s2;
	unsigned int	i;

	if (!s)
		return (NULL);
	s2 = (char *)s;
	i = 0;
	if (!(str = ft_strnew(ft_strlen(s2))))
		return (NULL);
	while (s2[i])
	{
		str[i] = f(i, s2[i]);
		i++;
	}
	return (str);
}
