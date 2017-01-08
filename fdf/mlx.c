/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 17:15:34 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/08 20:39:03 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Initialize variables
*/
void	init_variables(t_3d *d)
{
	d->offs.x = 100;
	d->offs.y = 400;
	d->zoom = 6;
	d->depth = 3125;
	d->img = NULL;
	//ft_putendl("global varibles initialized");
}
