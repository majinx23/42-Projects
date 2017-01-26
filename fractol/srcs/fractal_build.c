/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:19:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/26 16:50:59 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Initialize fractals
*/

void		init_fractal(t_3d *d, char *name)
{
	if (!ft_strcmp(name, "Mandelbrot"))
		init_mandelbrot(d);
	else if (!ft_strcmp(name, "Phoenix"))
		init_phoenix(d);
	else if (!ft_strcmp(name, "Julia"))
		init_julia(d);
	else if (!ft_strcmp(name, "Barnsey"))
		init_barnsley(d);
	else
		usage();
}

/*
** Main program
*/

void		fractol(t_3d *d)
{
	if (d->fractal == BARNSLEY)
	{
		init_barnsley(d);
		barnsley_fern_algo(&d->f, d->c, 0, d);
	}
	else if (d->fractal == KOCH)
	{
		init_koch(d);
		koch_snowflake_algo(d);
	}
	else
	{
		d->i.y = 0;
		while (d->i.y < HEIGHT)
		{
			d->i.x = -1;
			while (++d->i.x < WIDTH)
				get_fractal(d);
			++d->i.y;
		}
	}
	mlx_put_image_to_window(d->img.mlx, d->img.win, d->img.image, 0, 0);
	settings_background(d);
}

/*
** depending on chosen fractal will display it to the screen
*/

void		get_fractal(t_3d *d)
{
	t_cnb		z;
	t_cnb		c;
	unsigned	color;

	c.real = (d->i.x + d->offset.x) / (double)d->zoom + d->max.x;
	c.imag = (d->i.y + d->offset.y) / (double)d->zoom + d->max.y;
	z = (t_cnb) {.real = 0, .imag = 0};
	color = 0;
	if (d->fractal == MANDELBROT)
		mandelbrot(d, z, c);
	else if (d->fractal == JULIA)
		julia(d, c);
	else if (d->fractal == PHOENIX)
	{
		phoenix(d, z, c);
		color = 0xffffff;
	}
	(d->f.i == d->f.max) ? put_pixel_in_img(d, d->i.x, d->i.y, color) :
		put_pixel_in_img(d, d->i.x, d->i.y, color_pixel(d, d->f.i));
}

/*
** trace a gradient line using starting color a and ending color b
*/

t_rgb2		ft_gradient(unsigned a, unsigned b, int pixel)
{
	t_rgb2	c;

	c.x.b = a & 0xFF;
	c.y.b = b & 0xFF;
	c.y.b = (c.y.b - c.x.b) / pixel;
	c.x.g = a >> 8 & 0xFF;
	c.y.g = b >> 8 & 0xFF;
	c.y.g = (c.y.g - c.x.g) / pixel;
	c.x.r = a >> 16 & 0xFF;
	c.y.r = b >> 16 & 0xFF;
	c.y.r = (c.y.r - c.x.r) / pixel;
	return (c);
}

/*
** function useful for Koch algorytm
*/

void		ft_draw_line(t_3d *d, t_cv a, t_cv b)
{
	t_max	dif;
	t_max	i;
	int		pixel;
	t_rgb2	grad;

	dif.x = fabs(b.x - a.x);
	dif.y = fabs(b.y - a.y);
	pixel = (dif.x > dif.y) ? dif.x : dif.y;
	!pixel ? pixel = 1 : 0;
	i.x = dif.x / pixel * (a.x < b.x ? 1 : -1);
	i.y = dif.y / pixel * (a.y < b.y ? 1 : -1);
	grad = ft_gradient(a.color, b.color, pixel);
	while (pixel--)
	{
		put_pixel_in_img(d, a.x, a.y, ft_rgb2hex(grad.x));
		a.x += i.x;
		a.y += i.y;
		grad.x.r += grad.y.r;
		grad.x.g += grad.y.g;
		grad.x.b += grad.y.b;
	}
}
