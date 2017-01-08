/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:29:07 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/08 20:38:08 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
int			user_input(int keycode, t_3d *d)
{
   printf("ok%d\n", keycode);
	if (keycode == 53)
	{
		close_window(d);
		exit(0);
		return (0);
	}
	if (keycode == 69)
	{
		d->zoom *= 1.25;
		// erase and rewrite pixels
	}
	else if (keycode == 78)
	{
		d->zoom *= 0.80;
	}
   return (1);
}
*/
/*
 ** Converting points from 2d to 3d
 */
int			convert_3_to_2d(t_3d *d)
{
	t_index		i;

	//printf("convert_3_to_2d\n");
	if (!(d->n = (t_fxy **)malloc(sizeof(t_fxy *) * d->y)))
		return (0);
	i.y = 0;
	//ft_putendl("AA");
	while (i.y < d->y)
	{
		if (!(d->n[i.y] = (t_fxy *)malloc(sizeof(t_fxy) * d->x)))
			return (0);
		i.x = 0;
		while (i.x < d->x)
		{
			//printf("x: %i y: %i d->m: %i\n",i.x, i.y, d->m[i.y][i.x]);
			d->n[i.y][i.x].y = d->offs.y + d->zoom * get_3d_y(i.x, i.y,
					d->m[i.y][i.x], d);
			d->n[i.y][i.x].x = d->offs.x + d->zoom * get_3d_x(i.x, i.y);
			//printf("(y, x)(%lf, %lf) ", d->n[i.y][i.x].y, d->n[i.y][i.x].x);

			//d->p[i.y][i.x].x = (d->x + d->y) + i.x + i.y;
			//d->p[i.y][i.x].y = d->margin_top + d->n[i.y][i.x];
			++i.x;
		}
		//printf("\n");
		++i.y;
	}
	//ft_putendl("coords converted");
	return (1);
}

/*
 ** Tracing vectors to link each pixels put


void	link_pixels(t_3d *d)
{
	t_xy	i;
	t_xy	p;
	float	dly;

	i.y = 0;
	while (i.y < d->y - 1)
	{
		i.x = 0;
		while (i.x < d->x - 1)
		{
			d->slope = (fabs(dy) > fabs(dx)) ? 1 : 0;
			if (d->slope)
			{
				p.y = i.y + 0.5;
				dly = dy / dx;
					p.x = d->p[i.y][i.x].x;
				if (dx > 0)
					while (p.x++ <= d->p[i.y][i.x + 1].x)
					{
						mlx_pixel_put(d->mlx, d->w, 6 * d->p[i.y][i.x].x,
								6 * d->p[i.y][i.x].y, NICE_BLUE);
						p.y += dly;
					}
				else
					while (p.x-- >= d->p[i.y][i.x + 1].x)
					{
						mlx_pixel_put(d->mlx, d->w, 6 * d->p[i.y][i.x].x, 
								6 * d->p[i.y][i.x].y, NICE_BLUE);
						p.y -= dly;
					}
				++i.x;
			}
			++i.y;
		}
	}
}

 ** Put pixels in order to get our map's isometric 3d representation
 ** (d->x + d->y) / 10 is to set 10% space on sides. (hence 1.2 * d->x + d->y)
 

int		put_pixels(t_3d *d)
{
	t_fxy	i;
	//	int		tile;

	d->mlx = mlx_init();
	d->w = mlx_new_window(d->mlx, WIDTH, HEIGHT, TITLE);
	//create_image(d);
	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
			d->c[(int)i.y][(int)i.x] = NICE_BLUE;
			printf("a.x : %f\n", d->n[(int)i.y][(int)i.x].x);
			if (i.x < d->x - 1)//
				printf("b.x : %f\n", d->n[(int)i.y][(int)i.x + 1].x);
			printf("d.x : %hd\n", d->x);
			printf("d.y : %hd\n", d->y);
			if (i.x < d->x - 1)
				draw(d, d->n[(int)i.y][(int)i.x], d->n[(int)i.y][(int)i.x + 1]);
			if (i.y < d->y - 1)
				draw(d, d->n[(int)i.y][(int)i.x], d->n[(int)i.y + 1][(int)i.x]);
			//mlx_pixel_put(d->mlx, d->w, 6 * d->p[i.y][i.x].x,
			//		6 * d->p[i.y][i.x].y, NICE_BLUE);
			i.x++;
		}
		i.y++;
	}
	//mlx_put_image_to_window(d->mlx, d->w, d->img, d->x_tr, d->y_tr);
	//	link_pixels(d);
	mlx_key_hook(d->w, user_input, d);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}
*/
// gcc tracing.c fdf.h -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
