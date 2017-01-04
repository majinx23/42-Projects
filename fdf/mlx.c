/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 17:15:34 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/04 18:25:06 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Initialize variables
*/
void	init_variables(t_3d *d)
{
	d->x_tr = 100;
	d->y_tr = 100;
	d->zoom = 6;
	d->offs = 100;
	d->img = NULL;
	ft_putendl("global varibles initialized");
}
