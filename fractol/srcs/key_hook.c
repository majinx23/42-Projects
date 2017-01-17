/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 05:47:09 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/17 15:20:23 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

static void	offset(int k, t_3d *d)
{
	short	offset;

	offset = 40;
	if (k == KEY_UP)
		d->offset.y += -offset;
	else if (k == KEY_DOWN)
		d->offset.y += offset;
	else if (k == KEY_RIGHT)
		d->offset.x += offset;
	else if (k == KEY_LEFT)
		d->offset.x += -offset;
	if (k == KEY_PAD_ADD)
	{
		d->f.max += offset * d->iter_coef;
		printf("baba");
	}
	else if (k == KEY_PAD_SUB)
	{
		d->f.max -= offset * d->iter_coef;
		d->f.max < 0 ? d->f.max = 0 : 0;
	}
}

static void	set_fractal(int k, t_3d *d)
{
	if (k == KEY_1)
		init_fractal(d, "Mandelbrot");
	else if (k == KEY_2)
		init_fractal(d, "Julia");
	else if (k == KEY_3)
		init_fractal(d, "Phoenix");
	else if (k == KEY_4)
		init_fractal(d, "Barnsey");
}

static void	set_color(int k, t_3d *d)
{
	if (k == KEY_PAD_0)
		d->color = 42;
	else if (k == KEY_PAD_1)
		d->color = 0;
	else if (k == KEY_PAD_2)
		d->color = 1;
	else if (k == KEY_PAD_3)
		d->color = 2;
	else if (k == KEY_PAD_4)
		d->color = 3;
	else if (k == KEY_PAD_5)
		d->color = 4;
	else if (k == KEY_PAD_6)
		d->color = 5;
	else if (k == KEY_PAD_7)
		d->color = 6;
}

int			key_hook(int k, t_3d *d)
{
	if (k == KEY_SPACE)
		d->julia_static = (!d->julia_static) ? 1 : 0;
	if (k == KEY_ESCAPE)
	{
		mlx_destroy_image(d->mlx, d->img);
		exit(0);
	}
	if (k == KEY_H)
		d->menu = d->menu ? 1 : 0;
	else
	{
		offset(k, d);
		set_fractal(k, d);
		set_color(k, d);
		d->rng = random() % 6;
	}
	mlx_destroy_image(d->mlx, d->img);
	init_img(d);
	fractol(d);
	return (k);
}
