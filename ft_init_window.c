/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initial_scale.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 18:06:08 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/20 18:15:09 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Credit : Jan Walsh
*/

#include "../incl/fdf.h"

/*
 * ** Creates a new window, and updates the image.
 * */

void	init_window(t_data *data, t_3d *d, char *input)
{
	get_win_size(d, data);
	data->w.mlx = mlx_new_window(data->mlx, data->w.w, data->w.h, input);
	update_image(data, d);
}

/*
 * ** Creates a new image, edits it, and puts in on the window.
 * */

void	update_image(t_data *data, t_3d *d)
{
	d->img.mlx = mlx_new_image(data->mlx, d->img.w, d->img.h);
	draw_image(data, d);
	mlx_put_image_to_window(data->mlx, data->w.mlx, data->img.mlx, data->img.pos.x,
			d->img.pos.y);
}

/*
 * ** Determines the initial window dimensions based off initial img dimensions.
 * */

void	get_win_size(t_3d *d, t_data *data)
{
	get_img_size(d, data);
	data->w.h = d->img.h;
	data->w.w = d->img.w;
}

/*
 * ** Determines the size of the image to create based on unit_size and zoom.
 * */

void	get_img_size(t_3d *d)
{
	float	height;
	float	width;

	get_2dimg
	height = data->d.max.y - data->d.min.y;
	width = data->d.max.x - data->d.min.x;
	d->img.h = height + FRAME_WIDTH * 2 * (d->unit_size + d->scaling);
	d->img.w = width + FRAME_WIDTH * 2 * (d->unit_size + d->scaling);
}

/*
 * ** Updates the 2d min max.
 * ** Updates the unit size based on the 2d min max, MAX_UNIT_SIZE, MAX_WIN_H,
 * ** MAX_WIN_W, MIN_WIN_H and MIN_WIN_W.
 * */

void	get_unit_size(t_data *d)
{
	float	height;
	float	width;

	get_d2(d);
	height = d->d2.max.y - d->d2.min.	y;
	width = d->d2.max.x - d->d2.min.x;
	d->unit_size = ((height + FRAME_WIDTH * 2) * MAX_UNIT_SIZE > MAX_WIN_H) ?
		MAX_WIN_H / (height + FRAME_WIDTH * 2) : MAX_UNIT_SIZE;
	d->unit_size = ((width + FRAME_WIDTH * 2) * d->unit_size > MAX_WIN_W) ?
		MAX_WIN_W / (width + FRAME_WIDTH * 2) : d->unit_size;
	d->unit_size = ((height + FRAME_WIDTH * 2) * d->unit_size < MIN_WIN_H) ?
		MIN_WIN_H / (height + FRAME_WIDTH * 2) : d->unit_size;
	d->unit_size = ((width + FRAME_WIDTH * 2) * d->unit_size < MIN_WIN_W) ?
		MIN_WIN_W / (width + FRAME_WIDTH * 2) : d->unit_size;


}
