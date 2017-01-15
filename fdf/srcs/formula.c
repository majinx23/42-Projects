/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 20:41:21 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/15 22:15:52 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

float		vector_len(int x, int y, int z)
{
	return (sqrt(x * x + y * y + z * z));
}

float		get_3d_y(t_vector a, float depth)
{
	depth = 0;
	return (a.y / 2 - a.x / 2 - 2 * a.z);
}

float		get_3d_x(t_vector a)
{
	return (a.x + a.y);
}

