/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 20:41:21 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/03 19:42:06 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float		vector_len(int x, int y, int z)
{
	return (sqrt(x * x + y * y + z * z));
}

float		get_3d_y(int x, int y, int z)
{
	return (2 * y / 2 - 2 * x / 2 - 4 * z);
}

float		get_3d_x(int x, int y)
{
	return (2 * x + 2 * y);
}

double		spher_theta(t_3d *d)
{
	return (acos(ft_clamp(d->z, -1, 1)));
}

double		spher_phi(t_3d *d)
{
	double	p;
	p = atan2(d->y, d->x);
	return (p < 0) ? p + 2 * M_PI : p;
}

int			cart_to_spher(t_3d *d)
{
	d->theta = acos(d->z);
	d->phi = atan2(d->y, d->x);
	return (1);
}

int			spher_to_cart(t_3d *d)
{
	d->x = cos(d->phi) * sin(d->theta);
	d->y = sin(d->phi) * sin(d->theta);
	d->z = cos(d->theta);
	return (1); 
}

t_3d		*rotate_point(t_3d *d, t_xy i)
{
	t_xyz	new;

	new.x = i.x;
	new.y = i.y;
	new.z = 0;
	return (d);
}
