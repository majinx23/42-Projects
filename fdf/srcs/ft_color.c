/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:23:45 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 12:44:18 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
** stores the needed gradiant color increase in c.y and starting color in c.x
** on bitwise operators: a & 0xFF is equivalent to a % 256  as 0xFF = 255.
** >> 8 is used to divide color by 2^8 = 256, removing blue, and then red.
** the more c.x.a is close to 0xff and the more it will be transparent.
*/

t_argb2				gradient(unsigned a, unsigned b, int pixel)
{
	t_argb2		c;

	c.x.b = a & 0xFF;
	c.y.b = b & 0xFF;
	c.y.b = (c.y.b - c.x.b) / pixel;
	c.x.g = a >> 8 & 0xFF;
	c.y.g = b >> 8 & 0xFF;
	c.y.g = (c.y.g - c.x.g) / pixel;
	c.x.r = a >> 16 & 0xFF;
	c.y.r = b >> 16 & 0xFF;
	c.y.r = (c.y.r - c.x.r) / pixel;
	c.x.a = a >> 24;
	c.y.a = b >> 24;
	c.y.a = (c.y.a - c.x.a) / pixel;
	return (c);
}

/*
** ssaw : 0 = spring, 1 = summer, 2 = autumn, 3 = winter.
** level : 0 lowest, 3 highest.
*/

static	unsigned	season(int ssaw, int level)
{
	unsigned season[4][5];

	season[0][0] = MIDNIGHT_BLUE;
	season[0][1] = NICE_BLUE;
	season[0][2] = LAWN_GREEN;
	season[0][3] = BROWN;
	season[0][4] = WHITE;
	season[1][0] = MIDNIGHT_BLUE;
	season[1][1] = CYAN;
	season[1][2] = NICE_BLUE;
	season[1][3] = RED;
	season[1][4] = WHITE;
	season[2][0] = MIDNIGHT_BLUE;
	season[2][1] = GOLD;
	season[2][2] = RED;
	season[2][3] = GOLD;
	season[2][4] = WHITE;
	season[3][0] = MIDNIGHT_BLUE;
	season[3][1] = CORAL;
	season[3][2] = SKY_BLUE;
	season[3][3] = NICE_BLUE;
	season[3][4] = WHITE;
	return (season[ssaw][level]);
}

/*
** Shiki no Uta ~ colors map using above function
*/

void				color_map(t_3d *d)
{
	t_index		i;
	float		range;

	range = d->z_max - d->z_min;
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = 0;
		while (i.x < d->max.x)
		{
			if (d->m[i.y][i.x].z < -50)
				d->c[i.y][i.x] = season(d->season, 0);
			else if (d->m[i.y][i.x].z < 0)
				d->c[i.y][i.x] = season(d->season, 1);
			else if (d->m[i.y][i.x].z < 0.45 * d->z_max)
				d->c[i.y][i.x] = season(d->season, 2);
			else if (d->m[i.y][i.x].z < 0.60 * d->z_max)
				d->c[i.y][i.x] = season(d->season, 3);
			else
				d->c[i.y][i.x] = season(d->season, 4);
			++i.x;
		}
		++i.y;
	}
}
