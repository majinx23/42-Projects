/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/19 09:53:04 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
** creates a new image
*/
void	create_image(t_3d *d)
{
//	printf("width : %d   height : %d", d->dimension.x, d->dimension.y);
	d->img ? mlx_destroy_image(d->mlx, d->img) : 0;
	mlx_clear_window(d->mlx, d->w);
	d->img = mlx_new_image(d->mlx, d->dimension.x, d->dimension.y);
	d->data_address = mlx_get_data_addr(d->img, &(d->bpp),
	&(d->line_size), &(d->endian));
}


/*
** Puts exactly one pixel in the image
** As d->c[y][x] is the color expressed as integer, we take the address
** of d->data_address and then cast it as (int *) before dereferencing to
** save color value inside.
*/
void	put_pixel_in_img(t_3d *d, t_vector a, t_argb c)
{
	int			x;
	int			y;
	unsigned	color;

	x = round(a.x) + d->offs.x;
	y = round(a.y) + d->offs.y;

	color = (ft_clamp((int)(round(c.r) + d->l.r - 1), 0, 0xff) << 16) +
		(ft_clamp((int)(round(c.g) + d->l.g - 1), 0, 0xff) << 8) +
		ft_clamp(round(c.b) + d->l.b - 1, 0, 0xff) +
		(ft_clamp(((int)round(c.a) + d->l.a - 1), 0, 0xff) << 24);
	if (x > 0 && y > 0 && x < d->dimension.x && y < d->dimension.y)
		*(int *)&d->data_address[(x * d->bpp / 8) +
			(y * d->line_size)] = color;
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
 */

/*
** draw lines between points (no bits)
*/
void	lines_draw(t_3d *d, t_vector a, t_vector b, t_uixy c)
{
	t_fxy		dif;
	t_fxy		i;
	int			pixel;
	t_argb2		grad;

	//printf("pixel coords: %f, %f\n", a.x, a.y);
	dif.x = fabs(b.x - a.x);
	dif.y = fabs(b.y - a.y);
	pixel = (dif.x > dif.y) ? dif.x : dif.y;
	!pixel ? pixel = 1 : 0;
	i.x = dif.x / pixel * (a.x < b.x ? 1 : -1);
	i.y = dif.y / pixel * (a.y < b.y ? 1 : -1);
	grad = gradient(c.x, c.y, pixel);
	while (pixel--)
	{
		//printf("draw pixel: %f, %f\n", a.x, a.y);
		put_pixel_in_img(d, a, grad.x);
		a.x += i.x;
		a.y += i.y;
		grad.x.r += grad.y.r;
		grad.x.g += grad.y.g;
		grad.x.b += grad.y.b;
		grad.x.a += grad.y.a;
	}
}

void	draw(t_3d *d)
{
	t_index	i;
	t_uixy	color;

	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = 0;
		while (i.x < d->max.x)
		{
			color.x = d->c[i.y][i.x];
			if (i.x < d->max.x - 1)
			{
				color.y = d->c[i.y][i.x + 1];
				lines_draw(d, d->mm[i.y][i.x], d->mm[i.y][i.x + 1], color);
			}
			if (i.y < d->max.y - 1)
			{
				color.y = d->c[i.y + 1][i.x];
				lines_draw(d, d->mm[i.y][i.x], d->mm[i.y + 1][i.x], color);
			}
			++i.x;
		}
		++i.y;
	}
}

int		fdf(t_3d *d)
{
//	apply_matrix(d);
	apply_matrix(d);
	create_image(d);
//	printf("draw %.f\n ", d->offs.x);
	draw(d);
//	printf("put image to window\n");
	mlx_put_image_to_window(d->mlx, d->w, d->img, 0, 0);
	if (d->help_display > 0)
		ft_settings(d);
	mlx_hook(d->w, KEYPRESS, KEYPRESSMASK, user_input, d);
	//mlx_key_hook(d->w,user_input, d);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}
