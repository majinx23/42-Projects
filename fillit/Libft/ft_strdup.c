/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:04:01 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 18:51:54 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocated sufficient memory for a copy of the string s1, does the copy,
** and returns a pointer to it. The pointer may subsequendly be used as an
** argument to the function free(3).
*/

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*new;

	if (!(new = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	return (ft_strcpy(new, src));
}
