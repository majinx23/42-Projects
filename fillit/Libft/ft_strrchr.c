/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 19:14:37 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 19:14:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Locates the last occurrence of c (converted to char) in the string pointed
** to by s. The terminating null character is considered to be part of the
** string; therefore if c is \0, the function locate the \0.
** Returns a pointer to the located character or NULL.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	l;
	char	*p;

	l = ft_strlen((char *)s) + 1;
	i = 0;
	p = NULL;
	while (i < l)
	{
		if (s[i] == (char)c)
			p = &((char*)s)[i];
		i++;
	}
	return (p);
}
