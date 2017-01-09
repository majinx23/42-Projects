/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:35:32 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/09 17:29:02 by angavrel         ###   ########.fr       */
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

float	**matrix_rotation_x(t_3d *d, float x)
{
	float	**m;

	m = identity_matrix();
	m[1][1] = cos(x);
	m[1][2] = sin(x);
	m[2][1] = -sin(x);
	m[2][2] = cos(x);
	return (m);
}

float	**matrix_rotation_y(t_3d *d, float y)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = cos(y);
	m[0][2] = sin(y);
	m[2][0] = -sin(y);
	m[2][2] = cos(y);
	return (m);
}

float	**matrix_rotation_z(t_3d *d, float z)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = cos(z);
	m[0][1] = -sin(z);
	m[1][0] = sin(z);
	m[1][1] = cos(z);
	return (m);
}
/*
float	apply_matrix()
{

}*/
