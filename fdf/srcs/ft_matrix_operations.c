/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 08:16:37 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 03:45:02 by angavrel         ###   ########.fr       */
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
	d->center.y = (HEIGHT - d->offs.y) / 2;//(max.y - min.y) / 2;
	d->center.x = (WIDTH - d->offs.x) / 2;//(max.x - min.x) / 2;
	d->center.y = (max.y - min.y) / 2;
	d->center.x = (max.x - min.x) / 2;
//	d->center.z = (max.z - min.z) / 2;
	d->center.z = 0;
}

/*
** matrix_tmp store information about current sea level set with z scaling 0.2
*/
void		apply_matrix(t_3d *d)
{
	t_index		i;

	if (d->matrix)
		ft_free_matrix(d->matrix);
	d->matrix = ft_identity_matrix(0, 1);
	d->matrix = ft_matrix_scaling(d->matrix, d->scaling);
//	d->matrix = ft_factor_matrix_free(d->matrix, d->matrix_tmp, 'R');
//	ft_print_matrix(d->matrix);
	d->matrix = ft_matrix_global_rotation(d->matrix, d->angle);
	d->matrix = ft_matrix_z_scaling(d->matrix, 0.25);
//	free_matrix(d->matrix_tmp);
	d->matrix_tmp = ft_copy_matrix(d->matrix);
	d->matrix = ft_matrix_z_scaling(d->matrix, d->depth);
	recalculate_center(d);
	//print_matrix(d->matrix);
	//	printf("matrix after scaling :\n");
	//	print_matrix(matrix_scaling(d->scaling));
	//	d->matrix_tmp = matrix_rotation_z(d->angle.z);
//	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.x, 'x'));
//	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.y, 'y'));
//	ft_putstr("matrix z before :\n\n");
//	ft_print_matrix(d->matrix);
//	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.z, 'z'));
//	ft_putstr("matrix z after :\n");
//	ft_print_matrix(d->matrix);
//	print_matrix(d->matrix);
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
}
/*
t_vector	carthesian(t_vector n)
{
	n.x = get_3d_x(n);
	n.y = get_3d_y(n);
	return (n);
}*/
