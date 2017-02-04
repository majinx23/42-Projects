/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorytms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:42:03 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 19:18:51 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Mathematician Adrien Douady's tribute to his peer Benoit Mandelbrot.
** https://en.wikipedia.org/wiki/Mandelbrot_set
*/

void		mandelbrot(t_3d *d, t_cnb z, t_cnb c)
{
	double	n;
	double	t;

	n = z.real * z.real + z.imag * z.imag;
	t = 0;
	d->f.i = 0;
	while (d->f.i < d->f.max && n < 4)
	{
		t = z.real;
		z.real = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.imag * t + c.imag;
		n = z.real * z.real + z.imag * z.imag;
		++d->f.i;
	}
}

/*
** Gaston Maurice Julia's algorytm coined to create Julia fractals
** https://en.wikipedia.org/wiki/Julia_set
*/

void		julia(t_3d *d, t_cnb z)
{


//	while (++v->i < v->imax && (v->zr * v->zr + v->zi * v->zi) < 4)
//	{
	//	v->tmp = v->zr;
	//	v->zr = (v->zr * v->zr) - (v->zi * v->zi) + v->jr;   
	
	// !!!!!!! v->jr d->julia.real

	//	v->zi = 2 * v->zi * v->tmp + v->ji;
//	}

	double	n;
	double	t;
	t_cnb	c;

	c = (t_cnb) {.real = -0.175, .imag = 0.177};
	n = z.real * z.real + z.imag * z.imag;
	t = 0;
	d->f.i = 0;
	while (d->f.i < d->f.max && n < 4)
	{
		t = z.real;
		z.real = t * t - z.imag * z.imag + d->julia.real;
		z.imag = 2 * z.imag * t + d->julia.imag;
		n = z.real * z.real + z.imag * z.imag;
		++d->f.i;
	}
}

/*
** Phoenix fractal algorytm
*/

void		phoenix(t_3d *d, t_cnb z, t_cnb c)
{
	double	n;
	t_cnb	t;

	n = z.real * z.real + z.imag * z.imag;
	t = (t_cnb) {.real = 0, .imag = 0};
	d->f.i = 0;
	while (d->f.i < d->f.max && n < 4)
	{
		z.imag = 2 * fabs(z.imag * z.real) + c.imag;
		z.real = t.real - t.imag - c.real;
		t.real = z.real * z.real;
		t.imag = z.imag * z.imag;
		n = t.real + t.imag;
		++d->f.i;
	}
}

/*
** Michael Barnsley coined this algorytm that creates a fern fractal
** https://en.wikipedia.org/wiki/Barnsley_fern
*/

void		barnsley_fern_algo(t_i *i, t_cnb c, float rng, t_3d *d)
{
	while (++i->i < i->max)
	{
		rng = ((float)rand()) / RAND_MAX;
		if (rng <= 0.01f)
		{
			c.real = 0;
			c.imag = 0.16f * c.imag;
		}
		else if (rng <= 0.06f)
		{
			c.real = -0.15f * c.real + 0.28f * c.imag;
			c.imag = 0.26f * c.real + 0.24f * c.imag + 0.44f;
		}
		else if (rng <= 0.14f)
		{
			c.real = 0.2f * c.real + -0.26f * c.imag;
			c.imag = 0.23f * c.real + 0.22f * c.imag + 1.6f;
		}
		else
			c = (t_cnb) {.real = 0.85f * c.real + 0.04f * c.imag,
				.imag = -0.04f * c.real + 0.85f * c.imag + 1.6f};
		d->c = (t_cnb) {.real = (c.real + 3) * 70, .imag = 800 - c.imag * 70};
		put_pixel_in_img(d, d->c.real + 300, d->c.imag, d->fern_motion);
	}
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