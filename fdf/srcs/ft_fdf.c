/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 14:44:26 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 15:18:01 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
 ** FDF creates a new image, apply matrix formulas and then draw the
 ** image, once the image is drawn it is put inside the frame and then
 ** the program patiently awaits other instructions from the user with mlx_hook
 */

int		ft_fdf(t_3d *d)
{
	ft_create_image(d);
	ft_apply_matrix(d);
	ft_draw(d);
	mlx_put_image_to_window(d->img.mlx, d->img.w, d->img.img, 0, 0);
	if (d->help_display > 0)
		ft_settings(d);
	mlx_hook(d->img.w, KEYPRESS, KEYPRESSMASK, ft_user_hook, d);
	mlx_loop(d->img.mlx);
	return (0);
}

/*
 ** variables initialization and also reset values
 ** offs.y is margin from highest point and offs.x margin from lowest point
 ** mind and maxd are the max x and max y array value of d->mm to be drawn
 ** zoom is to have a scale that fits the image
 ** angle is the way the map is oriented at the start
 ** center is the center of the image
 ** season is the current season (Spring)
 */

void	ft_init_variables(t_3d *d)
{
	t_vector	zoom;

	d->center.y = (d->m[d->max.y - 1][d->max.x - 1].y + d->m[0][0].y) / 2;
	d->center.y = (d->m[d->max.y - 1][d->max.x - 1].y + d->m[0][0].y) / 2;
	d->center.x = (d->m[d->max.y - 1][d->max.x - 1].x + d->m[0][0].x) / 2;
	d->offs.x = WIDTH / 2 - d->center.x;
	d->offs.y = HEIGHT / 2 - d->center.y;
	d->offs.z = 1;
	if (d->vertical_view)
		d->angle = (t_vector) {.x = 0,  .y = 0, .z = 0};
	else
		d->angle = (t_vector) {.x = 0.926,  .y = -0.21, .z = 0.42};
	d->l = (t_argb) {.a = 0, .r = 0, .g = 0, .b = 0};
	d->depth = 1;
	d->season = 0;
	zoom.x = WIDTH / d->max.y - 1;
	zoom.y = HEIGHT / d->max.x - 1;
	d->scaling.x = (zoom.x <= zoom.y) ? zoom.x : zoom.y;
	d->scaling.y = d->scaling.x;
	d->scaling.z = -d->scaling.x;
}

/*
** here matrix transformations are applied after the final rendering matrix
** has finished to be computed using angles, scaling.
** matrix_tmp store information about current sea level set with z scaling 0.2
** allowing the user to play with mountains amplitude without touching seas.
*/

void	ft_apply_matrix(t_3d *d)
{
	t_index	i;

	d->matrix_tmp = ft_identity_matrix(0, d->scaling.x);
	d->matrix = ft_identity_matrix(0, 1);
	d->matrix = ft_factor_matrix_free(d->matrix_tmp,
			ft_matrix_global_rotation(d->matrix, d->angle), 'B');
	d->matrix = ft_matrix_z_scaling(d->matrix, 0.25);
	d->matrix_tmp = ft_copy_matrix(d->matrix);
	d->matrix = ft_matrix_z_scaling(d->matrix, d->depth);
	ft_recalculate_center(d);
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = -1;
		while (++i.x < d->max.x)
		{
			d->mm[i.y][i.x] = (d->m[i.y][i.x].z > 0) ?
				ft_matrix_to_vector(d->matrix, d->m[i.y][i.x], d->center) :
				ft_matrix_to_vector(d->matrix_tmp, d->m[i.y][i.x], d->center);
		}
		++i.y;
	}
	ft_free_matrix(d->matrix);
	ft_free_matrix(d->matrix_tmp);
}

/*
 ** axis is the axis to be rotated, a being all axis simultaneously
 ** angles are converted from degrees to radians and then normalized 
 ** with while loops as 2 * PI corresponds to a whole rotation.
 ** https://en.wikipedia.org/wiki/Degree_(angle)
 */

void	ft_rotate(t_3d *d, char axis, char i)
{
	float	a;

	a = 7.5 * (PI / 180);
	if (axis == 'z' || axis == 'a')
		d->angle.z += (i == '+') ? a : -a;
	if (axis == 'y' || axis == 'a')
		d->angle.y += (i == '+') ? a : -a;
	if (axis == 'x' || axis == 'a')
		d->angle.x += (i == '+') ? a : -a;
	while (d->angle.x >= 2 * PI)
		d->angle.x -= 2 * PI;
	while (d->angle.y >= 2 * PI)
		d->angle.y -= 2 * PI;
	while (d->angle.z >= 2 * PI)
		d->angle.z -= 2 * PI;
	while (d->angle.x < 0)
		d->angle.x += 2 * PI;
	while (d->angle.y < 0)
		d->angle.y += 2 * PI;
	while (d->angle.z < 0)
		d->angle.z += 2 * PI;
}

void	ft_recalculate_center(t_3d *d)
{
	t_index		i;
	t_vector	max;
	t_vector	min;

	max = (t_vector) {.x = 0, .y = 0, .z = 0};
	min = (t_vector) {.x = 0, .y = 0, .z = 0};
	i.y = 0;
	while (i.y < d->max.y)
	{
		i.x = -1;
		while (++i.x < d->max.x)
		{
			(d->m[i.y][i.x].x > max.x) ? max.x = d->m[i.y][i.x].x: 0;
			(d->m[i.y][i.x].x < min.x) ? min.x = d->m[i.y][i.x].x: 0;
			(d->m[i.y][i.x].y > max.y) ? max.y = d->m[i.y][i.x].y: 0;
			(d->m[i.y][i.x].y < min.y) ? min.y = d->m[i.y][i.x].y: 0;
			(d->m[i.y][i.x].z > max.z) ? max.z = d->m[i.y][i.x].z: 0;
			(d->m[i.y][i.x].z < min.z) ? min.z = d->m[i.y][i.x].z: 0;
		}
		++i.y;
	}
	d->center.y = (max.y - min.y) / 2;
	d->center.x = (max.x - min.x) / 2;
	d->center.z = 0;
}
