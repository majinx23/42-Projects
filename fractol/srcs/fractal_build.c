/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:19:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 22:15:50 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Main program
*/

void		fractol(t_3d *d)
{
	if (d->fractal == BARNSLEY)
		init_barnsley(d);
	else if (d->fractal == KOCH)
		init_koch(d);
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

	z.real = (d->i.y - (WIDTH >> 1) + d->offset.x) / d->zoom;
	z.imag = (d->i.x - (HEIGHT >> 1) + d->offset.y) / d->zoom;
	c = (t_cnb) {.real = 0, .imag = 0};
	color = 0;
	if (d->fractal == MANDELBROT)
		mandelbrot(d, c, z);
	else if (d->fractal == JULIA)
		julia(d, z);
	else if (d->fractal == PHOENIX)
	{
		phoenix(d, c, z);
		color = 0xffffff;
	}
	(d->f.i == d->f.max) ? put_pixel_in_img(d, d->i.x, d->i.y, color) :
		put_pixel_in_img(d, d->i.x, d->i.y, color_pixel(d, d->f.i));
}


