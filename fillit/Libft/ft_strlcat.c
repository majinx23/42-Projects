/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:36:56 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 16:14:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Concatenates two strings Guarentees nul-terminating result as long as there
** is one byte free in dst. The byte for the \0 should be included in size.
** Behavior for overlapping strings is undefined.
*/

#include "libft.h"

unsigned int	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[j] && j < size)
		j++;
	while (src[i] && i + j + 1 < size)
	{
		dst[i + j] = src[i];
		i++;
	}
	if (j != size)
		dst[i + j] = '\0';
	return (j + ft_strlen(src));
}
