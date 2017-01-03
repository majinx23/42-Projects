/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/03 17:29:57 by angavrel         ###   ########.fr       */
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
}

/*
 ** puts exactly one pixel in the image
 */
void	put_pixel_in_image(t_3d *d, t_xy i)
{
	d->data_address[(i.x * d->bpp / 8) + i.y *
		d->line_size]= d->c[i.y][i.x];
}


/*
 ** draw line inside the image using bits
 */
void	vector2(t_3d *d, int ix, int iy, int color)
{
	unsigned		l;
	unsigned long	x;
	unsigned long	y;
	int				dx;
	int				dy;

	x = (long)(d->n[iy][ix].x * 512 << 9) + 256; // maybe remove cast in long later
	y = (long)(d->n[iy][ix].y * 512 << 9) + 256;
	dx = (d->n[iy][ix + 1].x - d->n[iy][ix].x) * 512;
	dy = (d->n[iy][ix + 1].y - d->n[iy][ix].y) * 512;
	l = 0;
	while (l < 512)
	{
		printf("x = d->p[i->y][i->x].x: %lu   x << 9 + 255 : %lu   x >> 9 : %lu\n", d->n[iy][ix].x * 512, x, (x >> 9));
		mlx_pixel_put(d->mlx, d->w, 100 + (x >> 9), 100 + (y >> 9), color);
		x += dx;
		y += dy;
		++l;
	}
}

/*
** draw lines between points (no bits)
*/
void	vector(t_3d *d, t_xy a, t_xy b)
{
	t_xy		dif;
	t_index		i;
	int			pixel;
	int			v = 0;

	printf("a.x : %ld  b.x : %ld  a.y: %ld  b.y: %ld\n", a.x, b.x, a.y, b.y);
	dif.x = labs(b.x - a.x);
	dif.y = labs(b.y - a.y);
	printf("dif.x : %ld\n  .y: %ld\n", dif.x, dif.y),
	i.x = (a.x < b.x) ? 1 : -1;
	i.y = (a.y < b.y) ? 1 : -1;
	pixel = (dif.x > dif.y) ? dif.x : dif.y;
	!pixel ? pixel = 1 : 0;
	float x_incr = dif.x / pixel;
	float y_incr = dif.x / pixel;

	printf("pixels: %i\n", pixel);
	//while (labs(b.x - a.x) && labs(b.y - a.y))
	while (v < pixel)
	{
		printf("draw pixel(%li, %li)\n", a.x, a.y);
		mlx_pixel_put(d->mlx, d->w, a.x, a.y, NICE_BLUE);
		//put_pixel_in_image(d, a);
		//a.x += i.x * dif.x / pixel;
		//a.y += i.y * dif.y / pixel;
		a.x += x_incr;
		a.y += y_incr;
		++v;
	}
}
