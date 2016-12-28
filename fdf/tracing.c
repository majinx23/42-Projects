/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:29:07 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/28 15:05:23 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	funct(int keycode, void *param)
{
	printf("ok%d\n", keycode);
	return (1);
}

int		main()
{
	void	*mlx;
	void	*w;
	int		x;
	int		y;

	mlx = mlx_init(); // create connection
	w = mlx_new_window(mlx, WIDTH, HEIGHT, "Test");
	y = 50;
	while (y < 150)
	{
		x = 50;
		while (x < 150)
		{
			mlx_pixel_put(mlx, w, x, y, HOT_PINK);
			x++;
		}
		y++;
	}
	mlx_key_hook(w, funct, 0);
	mlx_loop(mlx); // pixels' display is only at this point
	return (0);
}
