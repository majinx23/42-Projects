/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 08:16:37 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 15:11:58 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void		recalculate_center(t_3d *d)
{
	t_index		i;
	t_vector	max;
	t_vector	min;

	max = (t_vector) {.x = 0, .y = 0, .z = 0};
	min = (t_vector) {.x = 0, .y = 0, .z = 0};
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = -1;
		while (++i.x < d->max.x)
		{
			(d->m[i.y][i.x].x > max.x) ? max.x = d->m[i.y][i.x].x: 0;
			(d->m[i.y][i.x].x < min.x) ? min.x = d->m[i.y][i.x].x: 0;
			(d->m[i.y][i.x].y > max.y) ? max.y = d->m[i.y][i.x].y: 0;
			(d->m[i.y][i.x].y < min.y) ? min.y = d->m[i.y][i.x].y: 0;
			(d->m[i.y][i.x].z > max.z) ? max.z = d->m[i.y][i.x].z: 0;
			(d->m[i.y][i.x].z < min.z) ? min.z = d->m[i.y][i.x].z: 0;
		}
		++i.y;
	}
	d->center.y = (max.y - min.y) / 2;
	d->center.x = (max.x - min.x) / 2;
	d->center.z = 0;
}

/*
 ** matrix_tmp store information about current sea level set with z scaling 0.2
 */

void		apply_matrix(t_3d *d)
{
	t_index		i;

	d->matrix_tmp = ft_identity_matrix(0, d->scaling.x);
	d->matrix = ft_identity_matrix(0, 1);
	d->matrix = ft_factor_matrix_free(d->matrix_tmp,
			ft_matrix_global_rotation(d->matrix, d->angle), 'B');
	d->matrix = ft_matrix_z_scaling(d->matrix, 0.25);
	d->matrix_tmp = ft_copy_matrix(d->matrix);
	d->matrix = ft_matrix_z_scaling(d->matrix, d->depth);
	recalculate_center(d);
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = -1;
		while (++i.x < d->max.x)
		{
			d->mm[i.y][i.x] = (d->m[i.y][i.x].z > 0) ?
				ft_matrix_to_vector(d->matrix, d->m[i.y][i.x], d->center) :
				ft_matrix_to_vector(d->matrix_tmp, d->m[i.y][i.x], d->center);
		}
		++i.y;
	}
	ft_free_matrix(d->matrix);
	ft_free_matrix(d->matrix_tmp);
}
