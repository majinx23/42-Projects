/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:16:41 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/11 13:31:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates and returns an array of null-terminated strings which are the
** result of the separation of the input string s by the char c.
** If memory allocation fails, return NULL.
*/

#include "libft.h"

static size_t	get_word_count(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s || s[i] == '\0')
		return (0);
	if (s[i++] != c)
		count++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	word_count;
	size_t	i;
	size_t	j;
	char	**result;

	if (!s || !c)
		return (NULL);
	word_count = get_word_count((char*)s, c);
	if (!(result = (char **)ft_memalloc(sizeof(char *) * (word_count + 1))))
		return (NULL);
	result[word_count] = NULL;
	j = 0;
	while (s && word_count)
	{
		i = 0;
		while (s && *s == c)
			s++;
		while (s && *s != c && ++i)
			s++;
		if (!(result[j++] = ft_strsub(s - i, 0, i)))
			return (NULL);
		word_count--;
	}
	return (result);
}
