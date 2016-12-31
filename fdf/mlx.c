/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 17:15:34 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/31 19:48:35 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** opens a new window
*/
void	open_window(t_3d *d)
{
	d->x_tr = 0;
	d->x_tr = 0;
	d->zoom = 6;
	d->mlx = mlx_init();
	d->w = mlx_new_window(d->mlx, WIDTH * d->zoom, HEIGHT * d->zoom, TITLE);
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
