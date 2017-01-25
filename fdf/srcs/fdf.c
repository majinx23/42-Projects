/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 14:44:26 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/25 13:57:26 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
** FDF creates a new image, apply matrix formulas and then draw the
** image, once the image is drawn it is put inside the frame and then
** the program patiently awaits other instructions from the user with mlx_hook
*/

int		fdf(t_3d *d)
{
	ft_create_image(&(d->img));
	d->shade = (((d->angle.x < 3 * PI / 2) && (d->angle.x > PI / 2)) ||
	((d->angle.y < 3 * PI / 2) && (d->angle.y > PI / 2))) ? 1 : 0;
	apply_matrix(d);
	if (d->min_pixel.y < d->max_pixel.y && d->min_pixel.x < d->max_pixel.x)
		((d->mm[0][0].y > d->mm[d->max.y - 1][d->max.x - 1].y) && (d->mm[0][0].x > d->mm[d->max.y - 1][d->max.x - 1].x)) ? ft_draw_rev(d) : ft_draw(d);
	mlx_put_image_to_window(d->img.mlx, d->img.w, d->img.image, 0, 0);
	if (d->help_display > 0)
		ft_settings(d);
	mlx_hook(d->img.w, KEYPRESS, KEYPRESSMASK, user_hook, d);
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

void	init_variables(t_3d *d)
{
	t_vector	zoom;

	d->offset = (t_vector) {.x = 0, .y = 0, .z = 0};
	if (d->vertical_view == True)
		d->angle = (t_vector) {.x = 0, .y = 0, .z = 0};
	else
		d->angle = (t_vector) {.x = 0.926, .y = 6.07, .z = 0.62};
	d->l = (t_argb) {.a = 0, .r = 0, .g = 0, .b = 0};
	d->depth = 1;
	d->season = (d->map_had_color == True) ? 4 : 0;
	zoom.x = (WIDTH / d->max.y - 1) * 1.1;
	zoom.y = (HEIGHT / d->max.x - 1) * 1.1;
	d->scaling = (t_vector) {.x = 1, .y = 1, .z = 1};
//	d->scaling.x = (zoom.x <= zoom.y) ? zoom.x : zoom.y;
//	d->scaling.y = d->scaling.x;
//	d->scaling.z = d->scaling.x;
}

/*
** calculate the point that need to be drawn only.
*/

float	hypothenus(t_vector a, t_vector b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}


t_vector	ft_matrix_to_vector2(float **m, t_vector v, t_3d *d)
{
	t_vector	n;

	n.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3] * v.w + d->offset.x; //+ d->center.x;
	n.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3] * v.w + d->offset.y; //+ d->center.y;
	n.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3] * v.w;
	n.w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3] * v.w;
	return (n);
}


static void	calculate_frame_max_point(t_3d *d)
{
	t_index		i;
	t_vector	a;
	t_bool		max_coords_found;

	max_coords_found = False;
	i.y = d->min_pixel.y -1;
	while (max_coords_found == False && ++i.y < d->max.y)
	{
		i.x = d->min_pixel.x -1;
		while (++i.x < d->max.x)
		{
			a = ft_matrix_to_vector2(d->matrix_tmp, d->m[i.y][i.x], d);
			if (a.y >= d->max_vector.y || a.y > HEIGHT)
				break;
			if (a.x >= d->max_vector.x || a.x > WIDTH)
			{
				max_coords_found = True;
				d->max_pixel.x = i.x - 1;
				d->max_pixel.y = i.y - 1;
				break;
			}
		}
	}
/*	printf("\n\n");
	printf("starting coord : (%f, %f)\n", d->min_vector.y, d->min_vector.x);
	printf("index min point : (%d, %d)\n", d->min_pixel.y, d->min_pixel.x);	
	printf("ending coord : (%f, %f)\n", d->max_vector.y, d->max_vector.x);
	printf("index max point : (%d, %d)\n", i.y, i.x);
	printf("\n\n");*/
}

static void	calculate_frame_min_point(t_3d *d)
{
	t_index		i;
	t_vector	a;

	i.y = 0;
	while (i.y < d->max.y)
	{
		a = ft_matrix_to_vector2(d->matrix_tmp, d->m[i.y][d->min_pixel.x], d);
		if (a.y >= d->min_vector.y)
			break;
		++i.y;
	}
	i.x = 0;
	while (i.x < d->max.x)
	{
		a = ft_matrix_to_vector2(d->matrix_tmp, d->m[i.y][i.x], d);
		if (a.x >= d->min_vector.x)
			break;
		++i.x;
	}
	d->min_pixel = i;
}





static void	calculate_max_point(t_3d *d)
{
	t_index		i;
	double		radius;

	radius = 0;
	i.y = d->min_pixel.y;
	while (i.y < d->max.y - 1)
	{
		d->max_vector = ft_matrix_to_vector2(d->matrix_tmp, d->m[i.y][d->min_pixel.x], d);
//		printf("current point  : (%f, %f)\n", d->max_vector.y, d->max_vector.x);
		if (d->max_vector.y >= HEIGHT || d->max_vector.y < 0)
			break;
		++i.y;
	//		printf("max point y : %d, max point x : %d\n", i.y, i.x);

	}
//	printf("max point y : %d\n", i.y);
	i.x = d->min_pixel.x;
	while (i.x < d->max.x)
	{
//		printf("calculating x index : %d\n", i.x);
		d->max_vector = ft_matrix_to_vector2(d->matrix_tmp, d->m[i.y][i.x], d);
		if (d->max_vector.x >= WIDTH || d->max_vector.x < 0)
			break;
		++i.x;
	}
	d->max_pixel.y = i.y;
	d->max_pixel.x = i.x;
	printf("ending coord : (%f, %f)\n", d->max_vector.y, d->max_vector.x);
	printf("min point / max : (%dy, %dx) (%dy, %dx)\n", d->min_pixel.y, d->min_pixel.x, d->max_pixel.y, d->max_pixel.x);	
	printf("max point y : %d, max point x : %d\n", i.y, i.x);
	d->max_vector.x /= 2;
	d->max_vector.y /= 2;
	radius = hypothenus(d->min_vector,d->max_vector);
	d->min_vector.x = d->max_vector.x - radius;
	d->min_vector.y = d->max_vector.y - radius;
	d->max_vector.x += radius;
	d->max_vector.y += radius;
	//	printf("real starting coord : (%f, %f)\n", d->min_vector.y, d->min_vector.x);
//	printf("real ending coords y : %f, x : %f\n", d->max_vector.y, d->max_vector.x);
}

static void	calculate_min_point(t_3d *d)
{
	t_index		i;
	i.y = 0;

	while (i.y < d->max.y - 1)
	{
		d->max_vector = ft_matrix_to_vector2(d->matrix_tmp, d->m[i.y][d->min_pixel.x], d);
		if (d->max_vector.y >= 0)
			break;
		++i.y;
	}
	i.x = 0;
	while (i.x < d->max.x)
	{
		d->max_vector = ft_matrix_to_vector2(d->matrix_tmp, d->m[i.y][i.x], d);
		if (d->max_vector.x >= 0)
			break;
		++i.x;
	}
//	printf("starting coord : (%f, %f)\n", d->min_vector.y, d->min_vector.x);
	d->min_pixel = i;				
}

static void	calculate_points_inside_frame(t_3d *d)
{
	d->min_pixel = (t_index) {.x = 0, .y = 0};
	d->min_vector = (t_vector) {.x = 0, .y = 0, .z = 0};
	calculate_min_point(d);
	d->max_pixel = (t_index) {.x = 0, .y = 0};
	d->max_vector = (t_vector) {.x = 0, .y = 0, .z = 0};
	calculate_max_point(d);
//	calculate_frame_min_point(d);
//	calculate_frame_max_point(d);
//	recalculate_center(d);
	
	d->center.y = (d->min_vector.y + d->max_vector.y) / 2;
	d->center.x = (d->min_vector.x + d->max_vector.x) / 2;

//	printf("d->center coord : (%f, %f)\n", d->center.y, d->center.x);
//	printf("d->center y, x : (%d, %d)\n", (d->max_pixel.y - d->min_pixel.y + 1) / 2, (d->max_pixel.x - d->min_pixel.x + 1) / 2);
	d->offs.x = - d->center.x;
	d->offs.y = - d->center.y;
	
}


/*
** here matrix transformations are applied after the final rendering matrix
** has finished to be computed using angles, scaling.
** matrix_tmp store information about current sea level set with z scaling 0.2
** allowing the user to play with mountains amplitude without touching seas.
*/

void	apply_matrix(t_3d *d)
{
	t_index	i;

	d->matrix_tmp = ft_identity_matrix(0, d->scaling.x);
	calculate_points_inside_frame(d); // calcul of center and max min index to be drawn

	d->matrix = ft_identity_matrix(0, 1);
	d->matrix = ft_factor_matrix_free(d->matrix_tmp,
			ft_matrix_global_rotation(d->matrix, d->angle), 'B');
	d->matrix = ft_matrix_z_scaling(d->matrix, 0.25);
	d->matrix_tmp = ft_copy_matrix(d->matrix);
	d->matrix = ft_matrix_z_scaling(d->matrix, d->depth);
	i.y = d->min_pixel.y;
	while (i.y < d->max_pixel.y)
	{
		i.x = d->min_pixel.x - 1;
		while (++i.x < d->max_pixel.x)
		{
			d->mm[i.y][i.x] = //(d->m[i.y][i.x].z > 0) ?
				ft_matrix_to_vector(d->matrix, d->m[i.y][i.x], d->center);// :
			d->mm[i.y][i.x].y += d->offs.y + d->offset.y;
			d->mm[i.y][i.x].x += d->offs.x + d->offset.x;
			//	ft_matrix_to_vector(d->matrix_tmp, d->m[i.y][i.x], d->center);
		}
//		printf("calculating coord : (%d, %d)\n", i.y, i.x);
		++i.y;
	}
	ft_free_matrix(d->matrix);
	ft_free_matrix(d->matrix_tmp);
	ft_putendl("\n");
}

/*
** axis is the axis to be rotated, a being all axis simultaneously
** angles are converted from degrees to radians and then normalized
** with while loops as 2 * PI corresponds to a whole rotation.
** https://en.wikipedia.org/wiki/Degree_(angle)
*/

void	norm_rotation(t_3d *d, char axis, char i)
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

void	recalculate_center(t_3d *d)
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
			(d->m[i.y][i.x].x > max.x) ? max.x = d->m[i.y][i.x].x : 0;
			(d->m[i.y][i.x].x < min.x) ? min.x = d->m[i.y][i.x].x : 0;
			(d->m[i.y][i.x].y > max.y) ? max.y = d->m[i.y][i.x].y : 0;
			(d->m[i.y][i.x].y < min.y) ? min.y = d->m[i.y][i.x].y : 0;
			(d->m[i.y][i.x].z > max.z) ? max.z = d->m[i.y][i.x].z : 0;
			(d->m[i.y][i.x].z < min.z) ? min.z = d->m[i.y][i.x].z : 0;
		}
		++i.y;
	}
	d->center.y = (max.y - min.y) / 2;
	d->center.x = (max.x - min.x) / 2;
	d->center.z = 0;
}
