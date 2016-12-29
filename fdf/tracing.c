/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:29:07 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/29 23:23:30 by angavrel         ###   ########.fr       */
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

int		convert_2_to_3d(t_3d *d)
{
	t_xy	i;

	if (!(d->n = (float **)malloc(sizeof(float *) * d->y)))
		return (0);
	i.y = 0;
	ft_putstr("c");
	while (i.y < d->y)
	{
		if (!(d->n[i.y] = (float *)malloc(sizeof(float) * d->x)))
			return (0);
		i.x = 0;
		ft_putstr("d");
		while (i.x < d->x)
		{
			d->n[i.y][i.x] = get_3d_y(i.x, i.y, d->m[i.y][i.x]);
			++i.x;
				printf("d->x : %d i.x:%d d->m[x][y]: %f\n", d->x, i.x, d->m[i.y][i.x]);
		}
		ft_putstr("f");
		++i.y;
	}
	return (1);
}

int		put_pixels(t_3d *d)
{
	t_xy	i;
//	int		tile;
	int		offs;
	
	ft_putstr("a");
	if (!(convert_2_to_3d(d)))
		return (0);
	printf("ok");
	ft_putstr("b");
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
						offs + d->n[i.y][i.x], HOT_PINK);
			i.x++;
		}
		i.y++;
	}
//	mlx_key_hook(w, funct, 0);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}

// gcc tracing.c fdf.h -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
