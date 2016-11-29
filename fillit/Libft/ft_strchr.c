/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:35:54 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 18:45:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Locates the first occurrence of c (converted to char) in the string pointed
** to by s. The terminating null character is considered to be part of the
** string; therefore if c is \0, the function locates the \0.
** Returns a pointer to the located character or NULL if the character
** does not appear in the string.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (!c && !s[i])
		return ((char *)s + i);
	return (NULL);
}
