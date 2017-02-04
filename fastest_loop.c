/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fastest_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 01:08:19 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 02:50:30 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Original idea : B. Souchet https://github.com/BenjaminSouchet/Fill_Area
** using memory pointer this time
** 8 values fill an array, values are only between 0 and 255.
** very usefull to color an area sending 0xARGBARGB.
** Usage : gcc fastest_loop.c && time ./a.out
** ./a.out  0.23s for 1 000 000 000 values filling the array tab.
*/

#include <stdlib.h>
#include <stdio.h>

void	divide_80(long color, long h, long w)
{
	unsigned char	*tab;
	int				x;
	int				y;

	tab = (unsigned char *)malloc(sizeof(unsigned char) * (h * w) + 1);
	y = -1;
	while (++y < h)
	{
		x = 0;
		while (x < w)
		{
			*(long *)&tab[x + (y * w)] = color;
			*(long *)&tab[x + 8 + (y * w)] = color;
			*(long *)&tab[x + 16 + (y * w)] = color;
			*(long *)&tab[x + 24 + (y * w)] = color;
			*(long *)&tab[x + 32 + (y * w)] = color;
			*(long *)&tab[x + 40 + (y * w)] = color;
			*(long *)&tab[x + 48 + (y * w)] = color;
			*(long *)&tab[x + 56 + (y * w)] = color;
			*(long *)&tab[x + 64 + (y * w)] = color;
			*(long *)&tab[x + 72 + (y * w)] = color;
			x += 80;
		}
	}
	free(tab);
}

int		main(void)
{
	divide_80(0xffffffaaffffffaa, 1440, 2660);
	return (0);
}
