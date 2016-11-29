/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:30:34 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 18:09:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Locates the first occurence of c (converted to an unsigned char)
** in string s. Returns a pointer to the byte located, or NULL if
** no such byte exists within n bytes.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s2;
	size_t	i;

	s2 = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)(s2[i]) == (unsigned char)c)
			return (void *)&(s2[i]);
		i++;
	}
	return (NULL);
}
