/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:35:32 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/15 02:12:53 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

float	**matrix_magnitude(float depth)
{
	float	**m;

	m = identity_matrix();
	m[2][2] = depth;
	return (m);
}

float	**matrix_scaling(t_vector scaling)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = scaling.x;
	m[1][1] = scaling.y;
	m[2][2] = scaling.z;
	return (m);
}

float	**matrix_translation(t_vector offset)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = offset.x;
	m[1][1] = offset.y;
	m[2][2] = 0;
	m[3][3] = 0;
	return (m);
}

void	rotate(t_3d *d, char axis, char i)
{
	float	a;
	int		reset;

	reset = 2 * PI;
	a = (5.625 * PI) / 180;
	if (axis == 'z' || axis == 'a')
		d->angle.z += (i == '+') ? a : -a;
	if (axis == 'y' || axis == 'a')
		d->angle.y += (i == '+') ? a : -a;
	if (axis == 'x' || axis == 'a')
		d->angle.x += (i == '+') ? a : -a;
//	printf("angle x%f\n", d->angle.x);
//	printf("angle y%f\n", d->angle.y);
//	printf("angle z%f\n", d->angle.z);
	if (d->angle.z > reset || d->angle.z < 0)
		d->angle.z += d->angle.z < 0 ? reset : -reset;
	if (d->angle.y > reset || d->angle.y < 0)
		d->angle.y += d->angle.y < 0 ? reset : -reset;
	if (d->angle.x > reset || d->angle.x < 0)
		d->angle.x += d->angle.x < 0 ? reset : -reset;
	if (d->angle.z > (reset - 0.02) || d->angle.z < 0.02)
		d->angle.z = 0;
	if (d->angle.y > (reset - 0.02) || d->angle.y < 0.02)
		d->angle.y = 0;
	if (d->angle.y > (reset - 0.02) || d->angle.y < 0.02)
		d->angle.y = 0;
}

float	**matrix_rotation(float x, char axis)
{
	float	**m;

	m = identity_matrix();
	if (axis == 'x')
	{
		m[1][1] = cos(x);
		m[1][2] = sin(x);
		m[2][1] = -sin(x);
		m[2][2] = cos(x);
	}
	else if (axis == 'y')
	{
		m[0][0] = cos(x);
		m[0][2] = sin(x);
		m[2][0] = -sin(x);
		m[2][2] = cos(x);
	}
	else if (axis == 'z')
	{
		m[0][0] = cos(x);
		m[0][1] = -sin(x);
		m[1][0] = sin(x);
		m[1][1] = cos(x);
	}
	return (m);
}
