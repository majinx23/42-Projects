/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 17:15:34 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/03 17:14:26 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** opens a new window
*/
void	open_window(t_3d *d)
{
	d->x_tr = 100;
	d->y_tr = 100;
	d->zoom = 6;
	d->offs = 100;
	ft_putendl("global varibles initialized");
}

/*
** destroys an image previously created
*/
void	destroy_image(t_3d *d)
{
	mlx_destroy_image(d->mlx, d->img);
}

/*
** closes window on user input (esc button)
*/
void	close_window(t_3d *d)
{
	mlx_destroy_window(d->mlx, d->w);
}
