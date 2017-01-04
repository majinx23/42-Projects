/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/04 19:07:15 by angavrel         ###   ########.fr       */
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
	if (keycode == 69)
	{
		d->zoom *= 1.25;
	}
	else if (keycode == 78)
	{
		d->zoom *= 0.80;
	}
	return (1);
}

/*
 ** create a new image
 */
void	create_image(t_3d *d)
{
	d->img ? mlx_destroy_image(d->mlx, d->img) : 0;
	mlx_clear_window(d->mlx, d->w);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->data_address = mlx_get_data_addr(d->img, &(d->bpp),
			&(d->line_size), &(d->endian));
}

/*
 ** Puts exactly one pixel in the image
 ** As d->c[y][x] is the color expressed as integer, we take the address
 ** of d->data_address and then cast it as (int *) before dereferencing to
 ** save color value inside.
 */
void	put_pixel_in_image(t_3d *d, int x, int y, int color)
{
	if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
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


 ** draw lines between points (no bits)
 */
void	draw(t_3d *d, t_fxy a, t_fxy b, t_xy c)
{
	t_fxy		dif;
	t_fxy		i;
	int			pixel;
	int			gradiant_color;

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
	gradiant_color = (d->c[c.y][c.x] - d->c[c.y][c.x]) / pixel;
	while (pixel--)
	{
		printf("draw pixel(%lf, %lf)\n", a.x, a.y);//
		//mlx_pixel_put(d->mlx, d->w, round(a.x), round(a.y), NICE_BLUE);
		put_pixel_in_image(d, round(a.x), round(a.y), d->c[c.y][c.x]);
		a.x += i.x;
		a.y += i.y;
		d->c[c.y][c.x] += gradiant_color;
	}
}

int		put_pixels(t_3d *d)
{
	t_xy	i;
	d->mlx = mlx_init();
	d->w = mlx_new_window(d->mlx, WIDTH, HEIGHT, TITLE);
	create_image(d);
	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
		//	(!d->c[i.y][i.x]) ? d->c[i.y][i.x] = NICE_BLUE : 0;
			printf("a.x : %f\n", d->n[i.y][i.x].x);
			if (i.x < d->x - 1)
				printf("b.x : %f\n", d->n[i.y][i.x + 1].x);
			printf("d.x : %hd\n", d->x);
			printf("d.y : %hd\n", d->y);
			if (i.x < d->x - 1)
				draw(d, d->n[i.y][i.x], d->n[i.y][i.x + 1],
						d->c[i.y][i.x], d->c[i.y][i.x + 1]);
			if (i.y < d->y - 1)
				draw(d, d->n[i.y][i.x], d->n[i.y + 1][i.x],
						d->c[i.y][i.x], d->c[i.y + 1][i.x]);

			i.x++;
		}
		i.y++;
	}
	mlx_put_image_to_window(d->mlx, d->w, d->img, d->x_tr, d->y_tr);
	mlx_key_hook(d->w, user_input, d);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}
