/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:28:21 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 18:27:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Appends a copy of the null-terminated string s2 to the end of the null-
** terminated string s1, then add a terminating null character.
** Behavior is undefined for overlapping strings.
*/

#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	j;

	i = ft_strlen(s1);
	j = -1;
	while (s2[++j])
		s1[i + j] = s2[j];
	s1[i + j] = s2[j];
	return (s1);
}
