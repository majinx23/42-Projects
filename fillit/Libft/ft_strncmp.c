/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:49:02 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 16:15:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Compares two strings and returns a positive int if s1 > s2, 0 of s1 = s2,
** or a negative int if s1 < s2. The comparision is done with unsigned chars.
** Does not compare more than n chars.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) &&
			((unsigned char *)s1)[i] &&
			((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
