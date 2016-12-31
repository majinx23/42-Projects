/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/31 19:42:30 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** create a new image
*/
void	create_image(t_3d *d)
{
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->data_address = mlx_get_data_addr(d->img, &(d->bpp),
			&(d->line_size), &(d->endian));
	mlx_put_image_to_window(d->mlx, d->w, d->img, 50 + d->x_tr, 50 + d->y_tr);
}

/*
** puts exactly one pixel in the image
*/
void	put_pixel_in_image(t_3d *d, t_xy *i)
{
		d->data_address[(i->x * d->bpp / 8) + i->y *
			d->line_size]= d->c[i->y][i->x];
}


/*
** draw line inside the image using bits
*/
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
		mlx_pixel_put(d->mlx, d->w, 100 + (x >> 9), 100 + (y >> 9), color);
		x += dx;
		y += dy;
		++l;
	}
}

