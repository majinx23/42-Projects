/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:35:32 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/13 01:49:09 by angavrel         ###   ########.fr       */
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
			m[j][i] = (i == j) ? 1.0 : 0.0;
			++i;
		}
		++j;
	}
	return (m);
}

float	**matrix_scaling(t_vector v)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = v.x;
	m[1][1] = v.y;
	m[2][2] = v.z;
	return (m);
}

float	**matrix_translation(t_xy offset)
{
	float	**m;

	m = identity_matrix();
	m[0][3] = offset.x;
	m[1][3] = offset.y;
	return (m);
}

float	**matrix_rotation_x(float x)
{
	float	**m;

	m = identity_matrix();
	m[1][1] = cos(x);
	m[1][2] = -sin(x);
	m[2][1] = sin(x);
	m[2][2] = cos(x);
	return (m);
}

float	**matrix_rotation_y(float y)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = cos(y);
	m[0][2] = sin(y);
	m[2][0] = -sin(y);
	m[2][2] = cos(y);
	return (m);
}

float	**matrix_rotation_z(float z)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = cos(z);
	m[0][1] = -sin(z);
	m[1][0] = sin(z);
	m[1][1] = cos(z);
	return (m);
}
