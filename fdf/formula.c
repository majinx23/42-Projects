/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 20:41:21 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/22 22:52:59 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		vector_len(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
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
