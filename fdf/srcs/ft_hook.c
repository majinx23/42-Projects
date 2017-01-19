/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:23:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/19 21:30:14 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
** Variable initialization
** gamma ~ g, scaling ~ zoom, translation on x axis ~ offs.x
** z amplitude ~ depth, image and matrix set to NULL and identity_matrix
** map default colors ~ season {0, 3}, rotation around x axis ~ angle.x.
*/

void	init_variables(t_3d *d)
{
	d->offs.x = d->dimension.x / 2 - d->center.x;
	d->offs.y = d->dimension.y / 2 - d->center.y;
	d->offs = (t_vector) {.x = d->offs.x, .y = d->offs.y, .z = 1};
	d->scaling = (t_vector){.x = 5, .y = 5, .z = 5};
	d->angle = (t_vector) {.x = 0.883,  .y = 0.672, .z = 0.496};
	d->center = (t_vector) {.x = 0, .y = 0, .z = 0};
	d->l = (t_argb) {.a = 0, .r = 0, .g = 0, .b = 0};
	d->depth = 1;
	d->img = NULL;
	d->season = 0;
	d->matrix = identity_matrix(0, 1);
}

int		color_hook(int k, t_3d *d)
{
	if (k == 35)
	{
		d->season = (d->season < 3) ? d->season + 1 : 0;
		color_map(d);
	}
	else if (k == 47)
		d->l.a = ft_clamp((int)d->l.a + 4, 0, 0xff);
	else if (k == 43)
		d->l.a = ft_clamp((int)d->l.a - 4, 0, 0xff);
	else if (k == 25)
	{
		d->l.r = ft_clamp((int)d->l.r + 4, -0xff, 0x33);
		d->l.g = ft_clamp((int)d->l.g + 4, -0xff, 0x33);
		d->l.b = ft_clamp((int)d->l.b + 4, -0xff, 0x33);
	}
	else if (k == 29)
	{
		d->l.r = ft_clamp((int)d->l.r - 4, -0xff, 0x33);
		d->l.g = ft_clamp((int)d->l.g - 4, -0xff, 0x33);
		d->l.b = ft_clamp((int)d->l.b - 4, -0xff, 0x33);
	}
	return (1);
}

int		translation_hook(int k, t_3d *d)
{
	if (k >= 123 && k <= 126)
	{
		if (k == 123 || k == 124)
			d->offs.x += (k == 123) ? 20 : -20;
		else if (k == 125 || k == 126)
			d->offs.y += (k == 125) ? -20 : 20;
	}
	return (1);
}

int		rotation_hook(int k, t_3d *d)
{
	if (k == 18 || k == 19)
		(k == 18) ? rotate(d, 'z', '+') : rotate(d, 'z', '-');
	else if (k == 20 || k == 21)
		(k == 20) ? rotate(d, 'y', '+') : rotate(d, 'y', '-');
	else if (k == 23 || k == 22)
		(k == 23) ? rotate(d, 'x', '+') : rotate(d, 'x', '-');
	else if (k == 26 || k == 28)
		k == 26 ? rotate(d, 'a', '+') : rotate(d, 'a', '-');
	return (1);
}

int		scaling_hook(int k, t_3d *d)
{
		printf("pressing : %d\n", k);
	if ((k == 69 && d->scaling.x < 400) || (k == 78 && d->scaling.x > 0.1))
	{
		d->scaling.x *= (k == 69) ? 1.25 : 0.8;
		d->scaling.y *= (k == 69) ? 1.25 : 0.8;
		d->scaling.z *= (k == 69) ? 1.25 : 0.8;
		d->scaling.w = 1;
	}
	if (k == 12)// && //d->depth > 0.01)
	{
		d->depth *= 1.25;
		printf("increasing d->depth to : %f.2", d->depth);
	}
	else if (k == 14)// && d->depth < 5)
		d->depth *= 0.8;
	return (1);
}

/*
** variable k stands for keycode; button pushed by user
*/

int		user_input(int k, t_3d *d)
{
	if (k == 53)
	{
		free_all(d);
		mlx_destroy_window(d->mlx, d->w);
		exit(0);
		return (0);
	}
	else if (k == 49)
	{
		init_variables(d);
		fdf(d);
	}
	else if (k == KEY_H)
		d->help_display = (d->help_display == 1) ? 0 : 1;
	if ((k >= 18 && k <= 23) || k == 26 || k == 28)
		rotation_hook(k, d);
	scaling_hook(k, d);
	translation_hook(k, d);
	color_hook(k, d);
	fdf(d);
	return (1);
}
