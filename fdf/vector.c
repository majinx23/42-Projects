/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/31 15:13:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	vector(t_3d *d, int ix, int iy, int color)
{
	unsigned		l;
	unsigned long	x;
	unsigned long	y;
	int				dx;
	int				dy;
	
	x = (long)(d->p[iy][ix].x * 512 << 9) + 256;
	y = (long)(d->p[iy][ix].y * 512 << 9) + 256;
	dx = (d->p[iy][ix + 1].x - d->p[iy][ix].x) * 512;
	dy = (d->p[iy][ix + 1].y - d->p[iy][ix].y) * 512;
	l = 0;
	while (l < 512)
	{
		printf("x = d->p[i->y][i->x].x: %i   x << 9 + 255 : %lu   x >> 9 : %lu\n", d->p[iy][ix].x * 512, x, (x >> 9));
		mlx_pixel_put(d->mlx, d->w, x >> 9, y >> 9, color);
		x += dx;
		y += dy;
		++l;
	}
}

