/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:23:50 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/11 19:10:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		apply_matrix(t_3d *d)
{
	t_index		i;

	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
			d->mm[i.y][i.x] = apply_matrix_to_vector(d->matrix, d->m[i.y][i.x]);
			++i.x;
		}
		++i.y;
	}
}

t_vector	apply_matrix_to_vector(float **m, t_vector v)
{
	t_vector	n;

	n.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
	n.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
	n.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
	return (n);
}


float		**factor_matrix(float	**a, float **b)
{
	float	**m;
	t_xyz	i;

	i.y = -1;
	while (++i.y < 3 && (i.x = -1) != 0)
	{
		while (++i.x < 3 && (i.z = -1) != 0)
		{
			while (++i.z < 3)
				m[i.y][i.x] += a[i.y][i.z] * b[i.z][i.x];
		}
	}
	return (a);
}

void		rotate(t_3d *d, float angle, char axis)
{
	float	**m;
	if (axis == 'x')
		m = matrix_rotation_x(angle);
	else
		m = (axis == 'y') ? matrix_rotation_y(angle) :
			matrix_rotation_z(angle);
	d->matrix = factor_matrix(d->matrix, m);
	apply_matrix(d);
	free(m);
}
