/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:32:54 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 19:03:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Appends a copy of the null-terminated string s2 to the end of the
** null-terminated string s1, then adds a terminating'\0'.
** Will not append more than n characters from s2, and then adds '\0'.
** s1 and s2 should not overlap, as behavior is undefined.
*/

#include "libft.h"

char	*ft_strncat(char *s1, char *s2, int nb)
{
	int	i;
	int	j;

	i = ft_strlen(s1);
	j = 0;
	while (s2[j] && j < nb)
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}
