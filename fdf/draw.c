/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/04 15:23:18 by angavrel         ###   ########.fr       */
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


** draw lines between points (no bits)
*/
void	draw(t_3d *d, t_fxy a, t_fxy b)
{
	t_fxy		dif;
	t_fxy		i;
	int			pixel;

	printf("a.x : %lf  b.x : %lf  a.y: %lf  b.y: %lf\n", a.x, b.x, a.y, b.y);//
	ft_putnbr(b.x);
	dif.x = fabs(b.x - a.x);
	dif.y = fabs(b.y - a.y);
	printf("dif x : %lf dif y: %lf\n", dif.x, dif.y);//
	pixel = (dif.x > dif.y) ? dif.x : dif.y;
	!pixel ? pixel = 1 : 0;
	i.x = dif.x / pixel * (a.x < b.x ? 1 : -1);
	i.y = dif.y / pixel * (a.y < b.y ? 1 : -1);
	printf("pixels: %i\n", pixel);//
	//while (labs(b.x - a.x) && labs(b.y - a.y))
	while (pixel--)
	{
		printf("draw pixel(%lf, %lf)\n", a.x, a.y);//
		mlx_pixel_put(d->mlx, d->w, round(a.x), round(a.y), NICE_BLUE);
		//put_pixel_in_image(d, a);
		a.x += i.x;
		a.y += i.y;
	}
}
