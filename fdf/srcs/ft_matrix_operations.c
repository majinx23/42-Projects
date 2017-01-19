/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 08:16:37 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/19 12:15:21 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	ft_print_matrix(float **m)//
{
	t_index	i;

	i.y = -1;
	while (++i.y < 4)
	{
		i.x = -1;
		while (++i.x < 4)
		{
			printf("%.1f ", m[i.y][i.x]);
		}
		printf("\n");
	}
}
/*
int			convert_3_to_2d(t_3d *d)
{
	t_index		i;

	apply_matrix(d);
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = 0;
		while (i.x < d->max.x)
		{
			//printf("center x %.1f \n", d->center.x);
			//printf("center y %.1f \n", d->center.y);
			d->mm[i.y][i.x] = apply_matrix_to_point(d->matrix, d->m[i.y][i.x], d->center);
	//		d->n[i.y][i.x].y = d->offs.y + d->zoom * 
	//			get_3d_y(d->mm[i.y][i.x], d->depth);
	//		d->n[i.y][i.x].x = d->offs.x + d->zoom * 
	//			get_3d_x(d->mm[i.y][i.x]);
			++i.x;
			//printf("(%.1f, %.1f)", d->n[i.y][i.x].x, d->n[i.y][i.x].y);
		}
		//	printf("\n");
		++i.y;
	}
	return (1);
}
*/
void		recalculate_center(t_3d *d)
{
	d->center.y = (d->m[d->max.y - 1][d->max.x - 1].y + d->m[0][0].y) / 2;
	d->center.x = (d->m[d->max.y - 1][d->max.x - 1].x + d->m[0][0].x) / 2;
	d->center.z = (d->m[d->max.y - 1][d->max.x - 1].z + d->m[0][0].z) / 2;
}

// 


void		apply_matrix(t_3d *d)
{
	t_index		i;

	//print_matrix(d->matrix);
	//	printf("matrix after scaling :\n");
	//	print_matrix(matrix_scaling(d->scaling));
	//	d->matrix_tmp = matrix_rotation_z(d->angle.z);
	d->matrix = factor_matrix(d->matrix, matrix_scaling(d->scaling));
	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.x, 'x'));
	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.y, 'y'));
	ft_putstr("matrix z before :\n\n");
	ft_print_matrix(d->matrix);
	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.z, 'z'));
	ft_putstr("matrix z after :\n");
	ft_print_matrix(d->matrix);
	d->matrix = factor_matrix(d->matrix, matrix_magnitude(d->depth));
//	print_matrix(d->matrix);
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = -1;
		while (++i.x < d->max.x)
			d->mm[i.y][i.x] = apply_matrix_to_point(d->matrix,
					d->m[i.y][i.x], d->center);
		++i.y;
	}
}

t_vector	carthesian(t_vector n)
{
	n.x = get_3d_x(n);
	n.y = get_3d_y(n);
	return (n);
}

t_vector	apply_matrix_to_point(float **m, t_vector v, t_vector c)
{
	t_vector	n;

	v.x -= c.x;
	v.y -= c.y;
	v.z -= c.z;
	n.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3] * v.w + c.x;
	n.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3] * v.w + c.y;
	n.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3] * v.w + c.z;
	n.w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3] * v.w;
	n = carthesian(n);
	return (n);
}

float		**factor_matrix(float **a, float **b)
{
	float		**m;
	t_index		i;
	short		k;

	m = identity_matrix();
	i.y = 0;
	while (i.y < 4)
	{
		i.x = 0;
		while (i.x < 4)
		{
			k = 0;
			while (k < 4)
			{
				m[i.y][i.x] += a[i.y][k] * b[k][i.x];
				++k;
			}
			++i.x;
		}
		++i.y;
	}
	return (m);
}

float		**sum_matrix(float **a, float **b)
{
	float		**m;
	t_index		i;
	short		k;

	m = identity_matrix();
	i.y = 0;
	while (i.y < 4)
	{
		i.x = 0;
		while (i.x < 4)
		{
			if (i.x == i.y)
				m[i.y][i.x] -= 1;
			k = 0;
			while (k < 4)
			{
				m[i.y][i.x] += a[i.y][k] + b[k][i.x];
				++k;
			}
			++i.x;
		}
		++i.y;
	}
	return (m);
}

float		**identity_matrix(void)
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
			m[j][i] = (i == j) ? 1 : 0;
			++i;
		}
		++j;
	}
	return (m);
}
