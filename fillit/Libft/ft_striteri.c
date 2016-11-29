/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:36:28 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:40:45 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies a function to each character in the string s. The function takes the
** index of the char and the address of the char whose address is passed to it
** to be modifiable.
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int i;

	i = 0;
	while (s && s[i] && f && *f)
	{
		f(i, &(s[i]));
		i++;
	}
}
