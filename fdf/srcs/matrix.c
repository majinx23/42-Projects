/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:35:32 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/14 22:35:25 by angavrel         ###   ########.fr       */
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
	m[0][3] = offset.x;
	m[1][3] = offset.y;
	m[2][3] = offset.z;
	m[3][3] = offset.w;
	return (m);
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
