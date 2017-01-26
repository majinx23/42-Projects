/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 05:47:09 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/26 16:29:21 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Image translation function
*/

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
		d->f.max += offset * d->iter_coef;
	else if (k == KEY_PAD_SUB)
	{
		d->f.max -= offset * d->iter_coef;
		d->f.max < 0 ? d->f.max = 0 : 0;
	}
}

/*
** Clear image function
*/

void		ft_black_screen(t_3d *d)
{
	t_index	i;

	i.y = 0;
	while (i.y < HEIGHT)
	{
		i.x = 0;
		while (i.x < WIDTH)
		{
			put_pixel_in_img(d, i.x, i.y, 0);
			++i.x;
		}
		++i.y;
	}
	mlx_put_image_to_window(d->img.mlx, d->img.win, d->img.image, 0, 0);
}

/*
** Change fractal function
*/

static void	set_fractal(int k, t_3d *d)
{
	if (k == KEY_4 || k == KEY_5)
	{
		(!(d->a)) ? ft_black_screen(d) : ++d->a;
		if (k == KEY_5)
			init_koch(d);
		else
			init_barnsley(d);
	}
	else if (k == KEY_1)
		init_mandelbrot(d);
	else if (k == KEY_2)
		init_julia(d);
	else if (k == KEY_3)
		init_phoenix(d);
}

/*
** Color function
*/

static void	set_color(int k, t_3d *d)
{
	if (k == KEY_PAD_0)
		d->color = 0;
	else if (k == KEY_PAD_1)
		d->color = 1;
	else if (k == KEY_PAD_2)
		d->color = 2;
	else if (k == KEY_PAD_3)
		d->color = 3;
	else if (k == KEY_PAD_4)
		d->color = 4;
	else if (k == KEY_PAD_5)
		d->color = 5;
	else if (k == KEY_PAD_6)
		d->color = 6;
	else if (k == KEY_PAD_7)
		d->color = 7;
}

/*
** key hook
*/

int			key_hook(int k, t_3d *d)
{
	if (k == KEY_SPACE)
		d->julia_static = (!d->julia_static) ? 1 : 0;
	if (k == KEY_ESCAPE)
	{
		mlx_destroy_image(d->img.mlx, d->img.image);
		exit(0);
	}
	if (k == KEY_H)
		d->menu = d->menu ? 0 : 1;
	else
	{
		offset(k, d);
		set_fractal(k, d);
		set_color(k, d);
		d->rng = random() % 6;
	}
	mlx_destroy_image(d->img.mlx, d->img.image);
	init_img(d);
	fractol(d);
	return (k);
}
