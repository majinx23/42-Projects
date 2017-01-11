/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 17:15:34 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/11 15:49:53 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Initialize variables
*/
void	init_variables(t_3d *d)
{
	d->offs.x = 0.1 * (d->x + d->y);
	d->offs.y = d->x * 2;
	d->zoom = 6;
	d->depth = 3125;
	d->img = NULL;
	d->season = 0;
	d->g = 0;
	//ft_putendl("global varibles initialized");
}
