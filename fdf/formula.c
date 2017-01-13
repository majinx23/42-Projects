/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 20:41:21 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/13 19:08:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float		vector_len(int x, int y, int z)
{
	return (sqrt(x * x + y * y + z * z));
}

float		get_3d_y(int x, int y, int z, float depth)
{
	return (((float)y / 2 - (float)x / 2 - depth * z));
}

float		get_3d_x(int x, int y)
{
	return (x + y);
}

double		spher_theta(t_3d *d)
{
	return (acos(ft_clamp(d->z, -1, 1)));
}

