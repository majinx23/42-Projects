/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:13:52 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:41:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Concatenates s1 and s2 in a new string which was allocated enough memory
** with malloc. Returns a pointer to that new string.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	length;
	size_t	i;
	size_t	j;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	length = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (!(newstr = ft_memalloc(sizeof(char) * length)))
		return (NULL);
	i = 0;
	while (i < length && s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < length && s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}
