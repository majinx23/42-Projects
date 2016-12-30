/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 21:40:34 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/30 21:55:27 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	open_window(t_3d *d)
{
	d->mlx = mlx_init();
	d->w = mlx_new_window(d->mlx, WIDTH, HEIGHT, TITLE);
}

void	create_image(t_3d *d)
{
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->data_address = mlx_get_data_addr(d->img, &(d->bpp),
								&(d->s_lines), &(d->endian));
}

void	destroy_image(t_3d *d)
{
		mlx_destroy_image(d->mlx, d->img);
}

void	close_window(t_3d *d)
{
		mlx_destroy_window(d->mlx, d->w);
}
