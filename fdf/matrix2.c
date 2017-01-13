/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:23:50 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/13 19:08:43 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_matrix(float **m)
{
	t_index	i;

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


	//apply_matrix(d);
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = 0;
		while (i.x < d->max.x)
		{
			d->mm[i.y][i.x] = apply_matrix_to_point(d->matrix, d->m[i.y][i.x], d->center);
			d->n[i.y][i.x].y = /*d->offs.y + d->zoom * */
				get_3d_y(d->m[i.y][i.x].x,
						d->m[i.y][i.x].y, d->m[i.y][i.x].z * d->depth);
			d->n[i.y][i.x].x = /*d->offs.x + d->zoom * */
				get_3d_x(d->m[i.y][i.x].x, d->m[i.y][i.x].y);
			++i.x;
			printf("(%f, %f)", d->n[i.y][i.x].x, d->n[i.y][i.x].y);
		}
		printf("\n");
		++i.y;
	}
	return (1);
}

void		apply_matrix(t_3d *d)
{
	d->matrix = identity_matrix();
	//print_matrix(d->matrix);
//	printf("matrix after scaling :\n");
	d->matrix = factor_matrix(d->matrix, matrix_scaling(d->scaling));
//	print_matrix(matrix_scaling(d->scaling));
	d->matrix = factor_matrix(d->matrix, matrix_rotation_z(d->angle.z));
	//print_matrix(d->matrix);
	d->matrix = factor_matrix(d->matrix, matrix_rotation_y(d->angle.y));
	//print_matrix(d->matrix_tmp);
	d->matrix = factor_matrix(d->matrix, matrix_rotation_x(d->angle.x));
	//print_matrix(d->matrix);
//	d->matrix = factor_matrix(d->matrix, matrix_translation(d->offs));
	//d->matrix = d->matrix_tmp;
//	printf("matrix print finished\n");
	printf("angle z : %f\n",d->angle.z);
}

t_vector	apply_matrix_to_point(float **m, t_vector v, t_xy c)
{
	t_vector	n;

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
	float	a;

	a = (5.625 * PI) / 1800;
	if (axis == 'z' || axis == 'a')
		d->angle.z += (i == '+') ? a : -a;
	if (axis == 'y' || axis == 'a')
		d->angle.y += (i == '+') ? a : -a;
	if (axis == 'x' || axis == 'a')
		d->angle.x += (i == '+') ? a : -a;
	//	print_matrix(d->matrix);
	convert_3_to_2d(d);
	//	free(d->matrix);
	//	d->matrix = NULL;
}
