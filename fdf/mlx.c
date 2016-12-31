/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 17:15:34 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/31 18:15:35 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	open_window(t_3d *d)
{
	d->x_tr = 0;
	d->x_tr = 0;
	d->zoom = 6;
	d->mlx = mlx_init();
	d->w = mlx_new_window(d->mlx, WIDTH * d->zoom, HEIGHT * d->zoom, TITLE);
}

void	create_image(t_3d *d)
{
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->data_address = mlx_get_data_addr(d->img, &(d->bpp),
								&(d->line_size), &(d->endian));
	mlx_put_image_to_window(d->mlx, d->w, d->img, 50 + d->x_tr, 50 + d->y_tr);
}

void	set_pixel_in_image(t_3d *d, t_xy *i)
{
	d->data_address[i->x * d->bpp / 8 + i->y * d->line_size] = d->c[i->y][i->x];
}

void	destroy_image(t_3d *d)
{
		mlx_destroy_image(d->mlx, d->img);
}

void	close_window(t_3d *d)
{
		mlx_destroy_window(d->mlx, d->w);
}
