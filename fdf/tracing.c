/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:29:07 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/30 16:05:19 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
int	funct(int keycode, void *param)
{
	printf("ok%d\n", keycode);
	return (1);
}
*/


/*
** Converting points from 2d to 3d
*/
int		convert_2_to_3d(t_3d *d)
{
	t_xy	i;

	if (!(d->n = (float **)malloc(sizeof(float *) * d->y)))
		return (0);
	i.y = 0;
	while (i.y < d->y)
	{
		if (!(d->n[i.y] = (float *)malloc(sizeof(float) * d->x)))
			return (0);
		i.x = 0;
		while (i.x < d->x)
		{
			d->n[i.y][i.x] = get_3d_y(i.x, i.y, d->m[i.y][i.x]);
			++i.x;
		}
		++i.y;
	}
	return (1);
}

/*
** Tracing vectors to link each pixels put
*/
void	link_pixels(t_3d *d)
{
	float	vector;
	t_xy	i;

	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
			vector = vector_len(i.x, i.y, d->m[i.y][i.x]);
			++i.x;
		}
		++i.y;
	}
}

/*
** Put pixels in order to get our map's isometric 3d representation
*/

int		put_pixels(t_3d *d)
{
	t_xy	i;
//	int		tile;
	int		offs;
	
	ft_putstr("b");//
	d->mlx = mlx_init(); // create connection
	d->w = mlx_new_window(d->mlx, WIDTH, HEIGHT, "FDF");
	i.y = 0;
	offs = 100;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
				mlx_pixel_put(d->mlx, d->w, offs + i.x + i.y,
						offs + d->margin_top  + d->n[i.y][i.x], NICE_BLUE);
			i.x++;
		}
		i.y++;
	}
	link_pixels(d);
//	mlx_key_hook(w, funct, 0);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}

// gcc tracing.c fdf.h -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
