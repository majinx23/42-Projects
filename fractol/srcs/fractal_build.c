/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:19:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/17 16:05:10 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
 ** Initialize fractals
 */

static	void init_barnsley(t_3d *d)
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
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	menu(d);
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
	(d->f.i == d->f.max) ? put_pixel_to_img(d, d->i.x, d->i.y, color) :
		put_pixel_to_img(d, d->i.x, d->i.y, color_pixel(d, &z, d->f.i));
}

void	init_julia_set(t_3d *d)
{
	d->max = (t_max) {.x = -1.5, .y = -1.5};
	d->offset = (t_index) {.x = 0, .y = 0};
	d->zoom = sqrt(WIDTH) * 10;
	d->f.max = sqrt(WIDTH) * 10;
	d->iter_coef = 1;
}

void	init_julia(t_3d *d)
{
	ft_putstr("julia");//
	init_julia_set(d);
	d->fractal = JULIA;
	d->max.y = -1.2;
	if (!d->rng)
		d->julia = (t_cnb) {.real = -0.506667, .imag = 0.520000 };
	else if (d->rng == 1)
		d->julia = (t_cnb) {.real = 0.403333, .imag = 0.273333 };
	else if (d->rng == 2)
		d->julia = (t_cnb) {.real = 0.386667, .imag = 0.103333 };
	else if (d->rng == 3)
		d->julia = (t_cnb) {.real = -0.203333, .imag = -0.696667 };
	else if (d->rng == 4)
		d->julia = (t_cnb) {.real = 0.18, .imag = -0.566667 };
	else if (d->rng == 5)
		d->julia = (t_cnb) {.real = 0.371504, .imag = -0.153893 };
}

void	init_mandelbrot(t_3d *d)
{
	ft_putstr("mandel");//
	init_julia_set(d);
	d->fractal = MANDELBROT;
	d->max = (t_max) {.x = -2.1, .y = -1.4};
	d->zoom = 280;
	d->f.max = 60;
}

void	init_phoenix(t_3d *d)
{
	init_julia_set(d);
	d->fractal = PHOENIX;
	d->max = (t_max) {.x = -1.3, .y = -1.8};
	d->f.max = 80;
	d->zoom = 250;
}



/*
 ** Mandelbrot
 */
void			mandelbrot(t_3d *d, t_cnb z, t_cnb c)
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
 ** Julia
 */
void			julia(t_3d *d, t_cnb z)
{
	double	n;
	double	t;
	t_cnb c;

	c = (t_cnb) {.real = -0.175, .imag = 0.177};
	n = z.real * z.real + z.imag * z.imag;
	t = 0;
	d->f.i = -1;
	while (++d->f.i < d->f.max && n < 4)
	{
		t = z.real;
		z.real = t * t - z.imag * z.imag + d->julia.real;
		z.imag = 2 * z.imag * t + d->julia.imag;
		n = z.real * z.real + z.imag * z.imag;
	}
}

/*
 ** Phoenix fractal
 */
void			phoenix(t_3d *d, t_cnb z, t_cnb c)
{
	double			n;
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

void	static	barnsley_fern_algo(t_i *i, t_cnb c, float rng, t_3d *d)
{
	while (++i->i < i->max)
	{
		rng = ((float)rand())/RAND_MAX;
		if (rng <= 0.01f)
		{
			c.real= 0;
			c.imag = 0.16f * c.imag;
		}
		else if (rng <= 0.06f){

			c.real = -0.15f *c.real + 0.28f * c.imag;
			c.imag = 0.26f *c.real + 0.24f * c.imag+ 0.44f;
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
		put_pixel_to_img(d, d->c.real, d->c.imag, d->fern_motion);
	}
}

void			barnsley(t_3d *d)
{
	unsigned		color;
	t_cnb	c;
	t_cnb	z;

	d->iter_coef = 500;

//	c.real = (d->i.x + d->offset.x) / (double)d->zoom + d->max.x;
//	c.imag = (d->i.y + d->offset.y) / (double)d->zoom + d->max.y;
	c = (t_cnb) {.real = 0, .imag = 0};
	z = (t_cnb) {.real = 0, .imag = 0};
		//	z = (t_cnb) {.real = 0, .imag = 0};
	color = 0;
	d->f.i = -1;
	d->f.max = 100;

	(d->fern <= 100) ? ++d->fern : 0;
	if (d->fern == 100)
		d->fern *= -2;
	d->fern_motion = (d->fern < 0) ? 0 : LIME;
	barnsley_fern_algo(&d->f, c, 0, d);
/*
	d->i.y = 0;
	while (d->i.y < HEIGHT)
	{
		d->i.x = 0;
		while (d->i.x < WIDTH)
		{
//			c.real = (d->i.x + d->offset.x) / (double)d->zoom + d->max.x;
//			c.imag = (d->i.y + d->offset.y) / (double)d->zoom + d->max.y;
		//	(d->f.i == d->f.max) ? put_pixel_to_img(d, d->i.x, d->i.y, color) :
			//	put_pixel_to_img(d, d->i.x, d->i.y, color_pixel(d, &z, LIME));
			++d->i.x;
		}
		++d->i.y;
	}*/
}
