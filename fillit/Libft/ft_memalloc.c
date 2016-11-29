/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:08:33 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 18:07:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Using malloc, allocates memory of size size and returns a pointer to it.
** The allocated memory is initialized at 0.
*/

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*p;

	if (!(p = malloc(size)))
		return (NULL);
	return (ft_memset(p, 0, size));
}
