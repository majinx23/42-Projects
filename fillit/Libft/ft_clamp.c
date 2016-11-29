/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:37:27 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 17:36:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Changes the value of int i to max if i > max, or to min if i < min.
*/

#include "libft.h"

int	ft_clamp(int min, int max, int i)
{
	if (i < min)
		i = min;
	if (i > max)
		i = max;
	return (i);
}
