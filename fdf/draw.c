/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/11 18:47:22 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		user_input(int keycode, t_3d *d)
{
	printf("ok%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx, d->w);
		exit(0);
		return (0);
	}
	else if (keycode == 69 && d->zoom < 300)
		d->zoom *= 1.25;
	else if (keycode == 78 && d->zoom > 1.25)
		d->zoom *= 0.80;
	else if (keycode == 123)
		d->offs.x -= d->zoom;
	else if (keycode == 124)
		d->offs.x += d->zoom;
	else if (keycode == 125)
		d->offs.y += d->zoom;
	else if (keycode == 126)
		d->offs.y -= d->zoom;
	else if (keycode == 12 && d->depth > 25)
		d->depth *= 0.80;
	else if (keycode == 14 && d->depth < 7600)
		d->depth *= 1.25;
	else if (keycode == 4)
		rotate_matrix(d, (90 * PI / 180) >> 24), 'z'); // TO BE CHANGED
	else if (keycode == 35)
	{
		d->season = (d->season < 3) ? d->season + 1 : 0;
		color_map(d);
	}
	else if (keycode == 47 && d->g < 0xf8)
		d->g = d->g + 8;
	else if (keycode == 43 && d->g)
		d->g = d->g - 8;
	if (keycode == 49) // reset for SPACE
		init_variables(d);
	fdf(d);
	return (1);
}

/*
 ** create a new image
 */
void	create_image(t_3d *d)
{
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
void	put_pixel_in_img(t_3d *d, int x, int y, unsigned color)
{
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
void	lines_draw(t_3d *d, t_fxy a, t_fxy b, t_uixy c)
{
	t_fxy		dif;
	t_fxy		i;
	int			pixel;
	t_argb2		grad;

	dif.x = fabs(b.x - a.x);
	dif.y = fabs(b.y - a.y);
	pixel = (dif.x > dif.y) ? dif.x : dif.y;
	!pixel ? pixel = 1 : 0;
	i.x = dif.x / pixel * (a.x < b.x ? 1 : -1);
	i.y = dif.y / pixel * (a.y < b.y ? 1 : -1);
	grad = gradient(c.x, c.y, pixel);
	c.x = 0;
	while (pixel--)
	{
		put_pixel_in_img(d, d->offs.x + round(a.x), d->offs.y + round(a.y),
				((int)round(grad.x.r) << 16) + ((int)round(grad.x.g) << 8)
				+ round(grad.x.b) + (((int)round(grad.x.a) + d->g) << 24));
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
	t_xy	i;
	t_uixy	color;

	i.y = -1;
	while (++i.y < d->y)
	{
		i.x = -1;
		while (++i.x < d->x)
		{
			if (!(color.x = d->c[i.y][i.x]))
				color.x = 0x00ff00;
			if (i.x < d->x - 1)
			{
				if (!(color.y = d->c[i.y][i.x + 1]))
					color.y = 0x00ff00;
				lines_draw(d, d->n[i.y][i.x], d->n[i.y][i.x + 1], color);
			}
			if (i.y < d->y - 1)
			{
				if (!(color.y = d->c[i.y + 1][i.x]))
					color.y = 0x00ff00;
				lines_draw(d, d->n[i.y][i.x], d->n[i.y + 1][i.x], color);
			}
		}
	}
}

int		fdf(t_3d *d)
{
	if (!convert_3_to_2d(d))
		return (ft_error("Conversion to isometric 3d failed"));
	//d->mlx = mlx_init();
	//d->w = mlx_new_window(d->mlx, WIDTH, HEIGHT, TITLE);
	create_image(d);
	draw(d);
	mlx_put_image_to_window(d->mlx, d->w, d->img, 0, 0);
	mlx_string_put(d->mlx, d->w, 10, 10, 0x33ffaa, "Click to display commands");
	mlx_hook(d->w, KEYPRESS, KEYPRESSMASK, user_input, d);
	//mlx_key_hook(d->w,user_input, d);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}
