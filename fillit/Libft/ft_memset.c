/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:29:40 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:16:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_memset writes len bytes of value c (converted to unsigned char)
** to the string b and returns b.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((char *)b)[i++] = (unsigned char)(c);
	return (b);
}
