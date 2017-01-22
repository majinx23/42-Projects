/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_global_rotation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 20:53:04 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 12:19:09 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftmath.h"

float	**ft_matrix_global_rotation(float **m, t_vector a)
{
	float		**tmp;
	float		t;

	t = 1000000;
	tmp = ft_identity_matrix(0, 1);
	tmp[0][0] = (((float)(int)(cos(a.y) * t)) / t)
		* (((float)(int)(cos(a.z) * t)) / t);

	tmp[0][1] = (((float)(int)(cos(a.z) * t)) / t)
		* (((float)(int)(sin(a.x) * t)) / t)
		* (((float)(int)(sin(a.y) * t)) / t) -
	(((float)(int)(cos(a.x) * t)) / t)
	* (((float)(int)(sin(a.z) * t)) / t);
	tmp[0][2] = (((float)(int)(cos(a.x) * t)) / t)
		* (((float)(int)(cos(a.z) * t)) / t)
		* (((float)(int)(sin(a.y) * t)) / t) +
	(((float)(int)(sin(a.x) * t)) / t)
	* (((float)(int)(sin(a.z) * t)) / t);
	tmp[1][0] = (((float)(int)(cos(a.y) * t)) / t)
		* (((float)(int)(sin(a.z) * t)) / t);
	tmp[1][1] = (((float)(int)(cos(a.x) * t)) / t)
		* (((float)(int)(cos(a.z) * t)) / t) +
		(((float)(int)(sin(a.x) * t)) / t) *
	(((float)(int)(sin(a.y) * t)) / t)
	* (((float)(int)(sin(a.z) * t)) / t);
	tmp[1][2] = (((float)(int)(-cos(a.z) * t)) / t)
		* (((float)(int)(sin(a.x) * t)) / t) + (((float)(int)(cos(a.x) * t)) / t) *
	(((float)(int)(sin(a.y) * t)) / t)
	* (((float)(int)(sin(a.z) * t)) / t);
	tmp[2][0] = (((float)(int)(-sin(a.y) * t)) / t);
	tmp[2][1] = (((float)(int)(cos(a.y) * t)) / t) * (((float)(int)(sin(a.x) * t)) / t);
	tmp[2][2] = (((float)(int)(cos(a.x) * t)) / t) * (((float)(int)(cos(a.y) * t)) / t);
	m = ft_factor_matrix_free(m, tmp, 'B');
	return (m);
}
