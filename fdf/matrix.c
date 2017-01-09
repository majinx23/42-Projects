/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:35:32 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/09 16:58:19 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	**identity_matrix(void)
{
	float	**m;
	short	i;
	short	j;

	if (!(m = (float**)malloc(sizeof(float*) * 4)))
		return (0);
	j = 0;
	while (j < 4)
	{
		if (!(m[j] = (float*)malloc(sizeof(float) * 4)))
			return (0);
		i = 0;
		while (i < 4)
		{
			m[j][i] = (i == j) ? 1.0f : 0.0f;
			++i;
		}
		++j;
	}
	return (m);
}

float	**matrix_rotation_x(t_3d *d, t_fxyz v)
{
	float	**m;

	m = identity_matrix();
	m[1][1] = cos(v.x);
	m[1][2] = sin(v.x);
	m[2][1] = -sin(v.x);
	m[2][2] = cos(v.x);
	return (m);
}

float	**matrix_rotation_y(t_3d *d, t_fxyz v)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = cos(v.y);
	m[0][2] = sin(v.y);
	m[2][0] = -sin(v.y);
	m[2][2] = cos(v.y);
	return (m);
}

float	**matrix_rotation_z(t_3d *d, t_fxyz v)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = cos(v.z);
	m[0][1] = -sin(v.z);
	m[1][0] = sin(v.z);
	m[1][1] = cos(v.z);
	return (m);
}
