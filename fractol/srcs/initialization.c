/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:02:54 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 15:58:52 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Mandelbrot is a specific case of Julia, same for Phoenix.
*/
void	init_julia_set(t_3d *d)
{
	d->max = (t_max) {.x = -1.5, .y = -1.5};
	d->offset = (t_index) {.x = 0, .y = 0};
	d->zoom = sqrt(WIDTH) * 10;
	d->f.max = sqrt(WIDTH) * 10;
	d->iter_coef = 1;
}

/*
** d->rng is a random value that will produce different Julia
** each time the user refresh Julia initialization
*/

void	init_julia(t_3d *d)
{
	init_julia_set(d);
	d->fractal =JULIA;
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

void	init_barnsley(t_3d *d)
{
	d->fractal = BARNSLEY;
	d->iter_coef = 500;
	d->f.i = -1;
//	d->f.max = 100;
	d->c = (t_cnb) {.real = 0, .imag = 0};
	d->fern_motion = LIME;
//	barnsley_fern_algo(&d->f, d->c, 0, d);
}

void	init_koch(t_3d *d)
{
	d->fractal = KOCH;
	d->koch_order = 4;
}
