/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:07:04 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:30:04 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Compares two strings and returns a positive int if s1 > s2, 0 of s1 = s2,
** or a negative int if s1 < s2. The comparision is done with unsigned chars.
*/

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (((unsigned char *)s1)[i] &&
			((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
