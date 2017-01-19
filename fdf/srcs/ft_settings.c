/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:21:49 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/19 15:21:51 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		ft_help_display(t_3d *d, unsigned color)
{
	short		x;

	x = 20;
	mlx_string_put(d->mlx, d->w, x, 15, color, "Press 'H' to close help and");
	mlx_string_put(d->mlx, d->w, x + 270, 15, RED, " SPEED UP");
	mlx_string_put(d->mlx, d->w, x + 360, 15, color, " the program");
	mlx_string_put(d->mlx, d->w, x, 40, color,
			"West, East, North, South : [<-] [->] [^] [v]");
	mlx_string_put(d->mlx, d->w, x, 65, color, "Zoom In / Out : [+] / [-]");
	mlx_string_put(d->mlx, d->w, x, 90, color, "Change Map : [1, 2, ...]");
	mlx_string_put(d->mlx, d->w, x, 115, color, "Change Color : [P]");
	mlx_string_put(d->mlx, d->w, x, 140, color,
			"Increase / Decrease Altitude : [Q] / [E]");
	mlx_string_put(d->mlx, d->w, x, 165, color,
			"Rotate around Z, Y, X, all axis : [1,2],[3,4],[5,6],[7,8]");
	mlx_string_put(d->mlx, d->w, x, 190, color,
			"Increase / Decrease brightness : [,] / [.]");
	mlx_string_put(d->mlx, d->w, x, 225, color,
			"Exit : [ESCAPE]");
}

void			ft_settings(t_3d *d)
{
	t_index		i;
	t_index		max;
	int			border;

	max.y = (d->help_display >> 1) ? 50 : 255;
	max.x = (d->help_display >> 1) ? 360 : 700;
	i.y = -1;
	border = 4;
	while (++i.y < max.y)
	{
		i.x = -1;
		while (++i.x < max.x)
		{
			if (i.x > border && i.x < max.x - border && i.y > border && i.y
					< max.y - border)
				mlx_pixel_put(d->mlx, d->w, i.x, i.y, SLIGHTLY_TRANSPARENT);
			else
				mlx_pixel_put(d->mlx, d->w, i.x, i.y, BLUE);
		}
	}
	if (d->help_display != 2)
		ft_help_display(d, HELP_COLOR);
	else
		mlx_string_put(d->mlx, d->w, 15, 10, HELP_COLOR,
			"Display Menu : Press [H] Button");
}
