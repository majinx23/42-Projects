/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:23:50 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/10 20:47:24 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_matrix(t_3d *d, float **m)
{
	t_index		i;
	float		w;

	i.y = 0;
	while (i.y < 4)
	{
		i.x = 0;
		while (i.x < 4)
		{ 
			d->ma.x = i.x * m[0][0] + i.y * m[1][0] + d->m[i.y][i.x] * m[2][0]
				+ m[3][0];
			d->ma.y = i.x * m[0][1] + i.y * m[1][1] + d->m[i.y][i.x] * m[2][1]
				+ m[3][1];
			d->ma.z = i.x * m[0][2] + i.y * m[1][2] + d->m[i.y][i.x] * m[2][2]
				+ m[3][2];
			w = i.x * m[0][3] + i.y * m[1][3] + d->m[i.y][i.x] * m[2][3]
				+ m[3][3];
			if (w != 1 && w != 0)
			{
				 d->ma.x /= w;
				 d->ma.y /= w;
				 d->ma.z /= w;
			}
			++i.x;
		}
		++i.y;
	}
}

void	rotate_matrix(t_3d *d, float n, char axis)
{
	float	**m;
	if (axis == 'x')
		m = matrix_rotation_x(n);
	else
		m = (axis == 'y') ? matrix_rotation_y(n) : matrix_rotation_z(n);
	apply_matrix(d, m);
	free(m);
}
