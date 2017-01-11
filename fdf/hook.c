/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 17:15:34 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/12 00:48:23 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Variable initialization
** gamma ~ g, scaling ~ zoom, translation on x axis ~ offs.x
** z amplitude ~ depth, image and matrix set to NULL and identity_matrix
** map default colors ~ season {0, 3}, rotation around x axis ~ angle.x.
*/

void	init_variables(t_3d *d)
{
	d->offs.x = 0.1 * (d->x + d->y);
	d->offs.y = d->x * 2;
	d->zoom = 6;
	d->depth = 3125;
	d->img = NULL;
	d->season = 0;
	d->l.r = 0;
	d->l.g = 0;
	d->l.b = 0;
	d->l.a = 0;
	d->angle.x = 0;
	d->angle.y = 0;
	d->angle.z = 0;
	d->matrix = identity_matrix();
}

/*
** Hook
*/

static	int	user_input3(int keycode, t_3d *d)
{
	if (keycode == 35)
	{
		d->season = (d->season < 3) ? d->season + 1 : 0;
		color_map(d);
	}
	else if (keycode == 47)
		d->l.a = ft_clamp((int)d->l.a + 4, 0, 0xff);
	else if (keycode == 43)
		d->l.a = ft_clamp((int)d->l.a - 4, 0, 0xff);
	else if (keycode == 25)
	{
		d->l.r = ft_clamp((int)d->l.r + 4, -0xff, 0xff);
		d->l.g = ft_clamp((int)d->l.g + 4, -0xff, 0xff);
		d->l.b = ft_clamp((int)d->l.b + 4, -0xff, 0xff);
	}
	else if (keycode == 29)
	{
		d->l.r = ft_clamp((int)d->l.r - 4, -0xff, 0xff);
		d->l.g = ft_clamp((int)d->l.g - 4, -0xff, 0xff);
		d->l.b = ft_clamp((int)d->l.b - 4, -0xff, 0xff);
	}
	return (1);
}

static	int	user_input2(int keycode, t_3d *d)
{
	if (keycode == 18 || keycode == 19)
		(keycode == 18) ? rotate(d, 'z', '+') : rotate(d, 'z', '-');
	else if (keycode == 20 || keycode == 21)
		(keycode == 20) ? rotate(d, 'y', '+') : rotate(d, 'y', '-');
	else if (keycode == 23 || keycode == 22)
		(keycode == 23) ? rotate(d, 'x', '+') : rotate(d, 'x', '-');
	else if (keycode == 26 || keycode == 28)
		(keycode == 26) ? rotate(d, 'a', '+') : rotate(d, 'a', '-');
	else if (keycode == 123 || keycode == 124)
		d->offs.x += (keycode == 123) ? -d->zoom : d->zoom;
	else if (keycode == 125 || keycode == 126)
		d->offs.y += (keycode == 125) ? d->zoom : -d->zoom;
	return (1);
}

int			user_input(int keycode, t_3d *d)
{
	printf("ok%d\n", keycode);//
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx, d->w);
		exit(0);
		return (0);
	}
	else if (keycode == 49)
		init_variables(d);
	else if (keycode == 69 && d->zoom < 300)
		d->zoom *= 1.25;
	else if (keycode == 78 && d->zoom > 1.25)
		d->zoom *= 0.80;
	else if (keycode == 12 && d->depth > 25)
		d->depth *= 0.80;
	else if (keycode == 14 && d->depth < 7600)
		d->depth *= 1.25;
	user_input2(keycode, d);
	user_input3(keycode, d);
	fdf(d);
	return (1);
}
