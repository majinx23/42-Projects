/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:29:07 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/31 19:38:57 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int			user_input(int keycode, t_3d *d)
{
   printf("ok%d\n", keycode);
	if (keycode == 53)
	{
		close_window(d);
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

/*
 ** Converting points from 2d to 3d
 */
int			convert_2_to_3d(t_3d *d)
{
	t_xy	i;

	if (!(d->n = (float **)malloc(sizeof(float *) * d->y)) ||
			!(d->p = (t_2p **)malloc(sizeof(t_2p **) * d->y)))
		return (0);
	i.y = 0;
	while (i.y < d->y)
	{
		if (!(d->n[i.y] = (float *)malloc(sizeof(float) * d->x)) ||
				!(d->p[i.y] = (t_2p *)malloc(sizeof(t_2p *) * d->x)))
			return (0);
		i.x = 0;
		while (i.x < d->x)
		{
			d->n[i.y][i.x] = get_3d_y(i.x, i.y, d->m[i.y][i.x]);
			d->p[i.y][i.x].x = (d->x + d->y) / 10 + i.x + i.y;
			d->p[i.y][i.x].y = d->offs + d->margin_top + d->n[i.y][i.x];
			++i.x;
		}
		++i.y;
	}
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
 */

int		put_pixels(t_3d *d)
{
	t_xy	i;
	//	int		tile;

	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{

			//vector(d, i.x, i.y, NICE_BLUE);
			//mlx_pixel_put(d->mlx, d->w, 6 * d->p[i.y][i.x].x,
			//		6 * d->p[i.y][i.x].y, NICE_BLUE);
			i.x++;
		}
		i.y++;
	}
	
	//	link_pixels(d);
	mlx_key_hook(d->w, user_input, d);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}

// gcc tracing.c fdf.h -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
