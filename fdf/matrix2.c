/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:23:50 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/13 00:40:15 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_matrix(float **m)
{
	t_xyz	i;

	i.y = -1;
	while (++i.y < 4)
	{
		i.x = -1;
		while (++i.x < 4)
		{
			printf("%f ", m[i.y][i.x]);
		}
		printf("\n");
	}
}

int			convert_3_to_2d(t_3d *d)
{
	t_index		i;

	apply_matrix(d);
	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
			d->mm[i.y][i.x] = apply_matrix_to_point(d->matrix,
					d->m[i.y][i.x], d->dimension);
			d->n[i.y][i.x].y = d->offs.y + /*d->zoom * */
				get_3d_y(d->mm[i.y][i.x].x,
						d->mm[i.y][i.x].y, d->mm[i.y][i.x].z, d);
			d->n[i.y][i.x].x = d->offs.x + /*d->zoom * */
				get_3d_x(d->mm[i.y][i.x].x, d->mm[i.y][i.x].y);
			++i.x;
		}
		++i.y;
	}
	return (1);
}

void		apply_matrix(t_3d *d)
{
	d->matrix_tmp = NULL;
	d->matrix = identity_matrix();
	//print_matrix(d->matrix);
	printf("matrix after scaling :\n");
	d->matrix_tmp = factor_matrix(d->matrix, matrix_scaling(d->scaling));
	print_matrix(matrix_scaling(d->scaling));
	d->matrix = factor_matrix(d->matrix_tmp, matrix_rotation_z(d->angle.z));
	//print_matrix(d->matrix);
	d->matrix_tmp = factor_matrix(d->matrix, matrix_rotation_y(d->angle.y));
	//print_matrix(d->matrix_tmp);
	d->matrix = factor_matrix(d->matrix_tmp, matrix_rotation_x(d->angle.x));
	//print_matrix(d->matrix);
	printf("matrix print finished\n");
}

t_vector	apply_matrix_to_point(float **m, t_vector v, t_index center)
{
	t_vector	n;
	t_index		c;

	c.x = center.x >> 1;
	c.y = center.y >> 1;
	v.x -= c.x;
	v.y -= c.y;
	n.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3] + c.x;
	n.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3] + c.y;
	n.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
	return (n);
}


float		**factor_matrix(float **a, float **b)
{
	float	**m;
	t_xyz	i;

	if (!(m = (float **)malloc(sizeof(float *) * 4)))
		return (0);
	i.y = 0;
	while (i.y < 4)
	{
		i.x = 0;
		if (!(m[i.y] = (float *)malloc(sizeof(float) * 4)))
			return (0);
		while (i.x < 4)
		{
			i.z = 0;
			while (i.z < 4)
			{
				m[i.y][i.x] += a[i.y][i.z] * b[i.z][i.x];
				++i.z;
			}
			++i.x;
		}
		++i.y;
	}
	return (m);
}


void		rotate(t_3d *d, char axis, char i)
{
	if (axis == 'z' || axis == 'a')
		d->angle.z = (i == '+') ? d->angle.z + (5.625 * PI) / 180 :
			d->angle.z - (5.625 * PI) / 180;
	if (axis == 'y' || axis == 'a')
		d->angle.y = (i == '+') ? d->angle.y + (5.625 * PI) / 180 :
			d->angle.y - (5.625 * PI) / 180;
	if (axis == 'x' || axis == 'a')
		d->angle.x = (i == '+') ? d->angle.x + (5.625 * PI) / 180 :
			d->angle.x - (5.625 * PI) / 180;
	//	print_matrix(d->matrix);
	convert_3_to_2d(d);
	//	free(d->matrix);
	//	d->matrix = NULL;
}
