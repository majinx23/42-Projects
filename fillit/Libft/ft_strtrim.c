/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:39:13 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 16:29:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates memory to and returns a copy of string s without spaces,
** newlines ('\n') and horizontal tabulations ('\t') at the beginning at end.
** If memory allocation fails, return NULL.
*/

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	char	*newstr;
	int		i;
	int		start;
	int		end;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s && is_space(s[i]))
		i++;
	if (s && !s[i])
		return (ft_memalloc(1));
	start = i;
	if (s && s[start] == '\0')
		return (ft_memalloc(1));
	end = ft_strlen(s) - 1;
	while (s && end >= 0 && s[end] && is_space(s[end]))
		end--;
	i = 0;
	if (!(newstr = (char *)ft_memalloc(sizeof(char) * (end - start + 2))))
		return (NULL);
	while (s && start <= end)
		newstr[i++] = s[start++];
	newstr[i++] = '\0';
	return (newstr);
}
