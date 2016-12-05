/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 20:57:54 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/03 21:24:18 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		max(int *tab, unsigned int len)
{
	int	max;
	int	i;

	if (len == 0)
		return (0);
	i = 0;
	max = tab[i];
	while (len--)
	{
		if (tab[i] > max)
			max = tab[i];
		++i;
	}
	return (max);
}
