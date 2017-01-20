/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_z_scaling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 20:12:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/20 21:25:42 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mathlibft.h"

float	**ft_matrix_z_scaling(float **matrix, float coefficient)
{
	float **matrix_tmp;

	matrix_tmp = ft_identity_matrix(0, 0);
	matrix_tmp[0][2] = coefficient * matrix[0][2];
	matrix_tmp[1][2] = coefficient * matrix[1][2];

	matrix[0][2] = matrix_tmp[0][2];
	matrix[1][2] = matrix_tmp[1][2];
	free(matrix_tmp);
	return (matrix);
}
