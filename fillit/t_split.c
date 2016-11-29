/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:10:33 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 15:02:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Splits the input string into substrings for each tetrimino.
*/

char	**t_split(char *s, short num)
{
	short	i;
	char	**result;

	if (!s || !(result = (char **)ft_memalloc(sizeof(char *) * (num + 1))))
		return (NULL);
	s = ft_strjoin(s, "\n");
	i = 0;
	while (*s != '\0' && num > 0)
	{
		if (!(result[i] = ft_strsub((char *)s, (T_SIZE + 1) * i, T_SIZE + 1)))
			return (NULL);
		num--;
		i++;
	}
	return (result);
}
