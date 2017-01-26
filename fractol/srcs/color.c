/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:19:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/26 17:09:43 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** d->color = 0 will produce rainbow hue
** d->color = 1 will make it irradiate
** 2 will color the inner shape with rainbow pixels
** 3 will make other color sets
** else it will be black and white
** 5 will be black and white (achromatic)
*/

static t_rgb	achromatic_color(t_rgb rgb)
{
	rgb.g = rgb.b;
	rgb.r = rgb.g;
	return (rgb);
}

unsigned		color_pixel(t_3d *d, int a)
{
	t_hsb	h;
	double	i;
	t_rgb	rgb;

	i = (double)a / d->f.max;
	h = (t_hsb) {.h = i * 360, .s = 1, .b = 1};
	if (d->color <= 2)
	{
		if (d->color == 0)
			h = (t_hsb) {.h = i * 360, .s = 1, .b = 1};
		else if (d->color == 1)
			h.h = i * ((float)rand()) / RAND_MAX * 4096;
		else if (d->color == 2)
			h.h = i * ((float)rand()) / RAND_MAX * 360;
		return (ft_hsb2hex(h));
	}
	rgb = ft_hex2rgb(ft_hsb2hex(h));
	if (d->color == 3)
		rgb.r = ft_fclamp((rgb.b + rgb.g) / 4, 0x30, 0xff);
	else if (d->color == 4)
		rgb.b = ft_fclamp((rgb.g + rgb.r) / 4, 0x30, 0xff);
	else
		rgb = achromatic_color(rgb);
	return (ft_rgb2hex(rgb));
}

void			init_koch(t_3d *d)
{
	d->fractal = KOCH;
	d->koch_order = 14;
}

static void		draw_fractal_line(t_3d *d, t_cv a, t_cv b, int depth)
{
	t_cv		tier_1;
	t_cv		tier_2;
	t_cv		pic;
	int			c;

	c = BLUE;
	if (depth <= 0)
		ft_draw_line(d, a, b);
	else
	{
		tier_1 = (t_cv) {(2.0 * a.x + b.x) / 3.0, (2.0 * a.y + b.y) / 3.0, c};
		tier_2 = (t_cv) {(a.x + 2.0 * b.x) / 3.0, (a.y + 2.0 * b.y) / 3.0, c};
		pic = (t_cv) {(a.x + b.x) / 2.0 - sqrt(3.0) * (b.y - a.y) / 6.0,
			(a.y + b.y) / 2.0 + sqrt(3.0) * (b.x - a.x) / 6.0, c};
		draw_fractal_line(d, a, tier_1, depth - 1);
		draw_fractal_line(d, tier_1, pic, depth - 1);
		draw_fractal_line(d, pic, tier_2, depth - 1);
		draw_fractal_line(d, tier_2, b, depth - 1);
	}
}

void			koch_snowflake_algo(t_3d *d)
{
	t_cv	a;
	t_cv	b;
	t_cv	c;

	a = (t_cv) {WIDTH / 3, HEIGHT / 3, RED};
	b = (t_cv) {2 * WIDTH / 3, HEIGHT / 3, WHITE};
	c = (t_cv) {WIDTH / 2, 2 * HEIGHT / 3, BLUE};
	draw_fractal_line(d, a, b, d->koch_order);
	draw_fractal_line(d, a, c, d->koch_order);
	draw_fractal_line(d, c, b, d->koch_order);
}
