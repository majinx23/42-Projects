/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_transformations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 08:22:47 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/19 15:19:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

float	**matrix_magnitude(float depth)
{
	float	**m;

	m = identity_matrix();
	m[2][2] = depth;
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


/*
** a is to rotate all axis simultaneously
*/
void	rotate(t_3d *d, char axis, char i)
{
	float	a;
//	d->matrix_tmp = identity_matrix();
	//	int		reset;
//	d->matrix = identity_matrix();
	//	reset = 2 * PI;
	a = (5.625 * M_PI) / 180;
	/*	if ((axis == 'z' || axis == 'a') && i == '+')
		d->angle.z += a;
		else if (axis == 'z' || axis == 'a')
		d->angle.z -= a;*/
	if (axis == 'z' || axis == 'a')
	{ 
	//	d->matrix = factor_matrix(d->matrix, matrix_rotation(0, 'z'));
		d->angle.z += (i == '+') ? a : -a;
//		d->matrix_tmp = matrix_rotation(d->angle.z, 'z');
	}
//	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.z, 'z'));
	if (axis == 'y' || axis == 'a')
	{
	//	d->matrix = factor_matrix(d->matrix, matrix_rotation(0, 'y'));
		d->angle.y += (i == '+') ? a : -a;
//		d->matrix_tmp = matrix_rotation(d->angle.y, 'y');
	}
//	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.y, 'y'));
	if (axis == 'x' || axis == 'a')
	{
	//	d->matrix = factor_matrix(d->matrix, matrix_rotation(0, 'x'));
		d->angle.x += (i == '+') ? a : -a;
//		d->matrix_tmp = matrix_rotation(d->angle.x, 'x');
	}
//	d->matrix = factor_matrix(d->matrix, matrix_rotation(d->angle.x, 'x'));
	//	printf("angle x%f\n", d->angle.x);
	//	printf("angle y%f\n", d->angle.y);
	//	printf("angle z%f\n", d->angle.z);
	/*	if (d->angle.z > reset || d->angle.z < 0)
		d->angle.z += d->angle.z < 0 ? reset : -reset;
		if (d->angle.y > reset || d->angle.y < 0)
		d->angle.y += d->angle.y < 0 ? reset : -reset;
		if (d->angle.x > reset || d->angle.x < 0)
		d->angle.x += d->angle.x < 0 ? reset : -reset;
		if (d->angle.z > (reset - 0.02) || d->angle.z < 0.02)
		d->angle.z = 0;
		if (d->angle.y > (reset - 0.02) || d->angle.y < 0.02)
		d->angle.y = 0;
		if (d->angle.y > (reset - 0.02) || d->angle.y < 0.02)
		d->angle.y = 0;*/
//	ft_putstr("matrix z before :\n\n");
//	ft_print_matrix(d->matrix);
//	d->matrix = factor_matrix(d->matrix_tmp, d->matrix);
//	ft_putstr("matrix z after :\n\n");
//	ft_print_matrix(d->matrix);
//	free(d->matrix_tmp);
//	d->matrix = matrix_rotation(d->angle);
//	d->matrix = matrix_global_rotation(d->angle);
}

float	**matrix_global_rotation(t_vector a)
{
	float	**m;

	m = identity_matrix();
	m[0][0] = cos(a.y) * cos(a.z);
	m[0][1] = cos(a.z) * sin(a.x) * sin(a.y) - cos(a.x) * sin(a.z);
	m[0][2] = cos(a.x) * cos(a.z) * sin(a.y) + sin(a.x) * sin(a.z);
	m[1][0] = cos(a.y) * sin(a.z);
	m[1][1] = cos(a.x) * cos(a.z) + sin(a.x) * sin(a.y) * sin(a.z);
	m[1][2] = -cos(a.z) * sin(a.x) + cos(a.x) * sin(a.y) * sin(a.z);
	m[2][0] = -sin(a.y);
	m[2][1] = cos(a.y) * sin(a.x);
	m[2][2] = cos(a.x) * cos(a.y);
	return (m);
}

float	**matrix_rotation(float x, char axis)
{
	float	**m;

	m = identity_matrix();
	if (axis == 'x')
	{
		m[1][1] = cos(x);
		m[1][2] = -sin(x);
		m[2][2] = cos(x);
		m[2][1] = sin(x);
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
