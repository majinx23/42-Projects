/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:19:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 11:42:59 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
 ** Initialize fractals
 */

void init_barnsley(t_3d *d)
{
	d->fractal = BARNSLEY;
}

void	init_fractal(t_3d *d, char *name)
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
 ** create a color grandient, use value between 0 and 1530
 ** tiny numbers will give tiny colors
 */

int		ft_rainbow_gradient(double x)
{
	t_rgb	rgb;

	x = ft_fclamp(x, 0, 1);
	if (x < 0 || x > 1530)
		rgb = (t_rgb) {.r = 0xff, .g = 0, .b = 0};
	if (0 <= x && x < 255)
		rgb = (t_rgb) {.r = 0xff, .g = x, .b = 0};
	else if (255 <= x && x < 510)
		rgb = (t_rgb) {.r = 510 - x, .g = 0xff, .b = 0};
	else if (510 <= x && x < 765)
		rgb = (t_rgb) {.r = 0, .g = 0xff, .b = x - 510};
	else if (765 <= x && x < 1020)
		rgb = (t_rgb) {.r = 0, .g = 1020 - x, .b = 0xff};
	else if (x >= 1020 && x <= 1530)
		rgb = (t_rgb) {.r = x - 1020, .g = 0, .b = 0xff};
	else if (x >= 1275 && x <= 1530)
		rgb = (t_rgb) {.r = 0xff, .g = 0, .b = 1530 - x};
	return (ft_rgb2hex(rgb));
}

unsigned color_pixel(t_3d *d, t_cnb *z, int a)
{
	t_hsb		h;
	double		i;

	i = (double)a / d->f.max;
	if (d->color == 1)
		return (ft_rainbow_gradient(i));
	else if (d->color == 0)
		h = (t_hsb) {.h = i * 360, .s = 1, .b = 1};
	else if (d->color == 2)
		return (linear_interpolation(i));
	else
		h = (t_hsb) {.h = i, .s = fmod(z->imag, 1), .b = 1};
	return (ft_hsb2hex(h));
}

unsigned linear_interpolation(double hue)
{
	t_rgb	rgb;

	rgb.r = (1 - hue) * 0xff + hue * 0;
	rgb.g = (1 - hue) * 0xff + hue * 0;
	rgb.b = (1 - hue) * 0x00 + hue * 0xff;
	return (ft_rgb2hex(rgb));
}


/*
 ** Loop through every pixel
 */
void		fractol(t_3d *d)
{

	if (d->fractal == BARNSLEY)
		barnsley(d);
	else
	{
		d->i.y = 0;
		while (d->i.y < HEIGHT)
		{
			d->i.x = 0;
			while (d->i.x < WIDTH)
			{
				get_fractal(d);
				++d->i.x;
			}
			++d->i.y;
		}
		mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	}
	settings_background(d);
}

void		get_fractal(t_3d *d)
{
	t_cnb	z;
	t_cnb	c;
	unsigned		color;

	c.real = (d->i.x + d->offset.x) / (double)d->zoom + d->max.x;
	c.imag = (d->i.y + d->offset.y) / (double)d->zoom + d->max.y;
	z = (t_cnb) {.real = 0, .imag = 0};
	color = 0;
	if (d->fractal == MANDELBROT)
		mandelbrot(d, z, c);
	else if (d->fractal == JULIA)
		julia(d, c);
	else if (d->fractal == BARNSLEY)
		barnsley(d);
	else if (d->fractal == PHOENIX)
	{
		phoenix(d, z, c);
		color = 0xffffff;
	}
	(d->f.i == d->f.max) ? put_pixel_in_img(d, d->i.x, d->i.y, color) :
		put_pixel_in_img(d, d->i.x, d->i.y, color_pixel(d, &z, d->f.i));
}
