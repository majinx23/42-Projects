/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 05:55:43 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 11:24:56 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"


static void		settings(t_3d *d)
{
	short		x;

	x = 15;
	mlx_string_put(d->mlx, d->win, x, 10, HELP_COLOR,
			"Press 'H' to close help");
	mlx_string_put(d->mlx, d->win, x, 35, HELP_COLOR,
			"West, East, North, South : [<-] [->] [^] [v]");
	mlx_string_put(d->mlx, d->win, x, 60, HELP_COLOR,
			"Zoom : [Mouse wheel or right/left click]");
	mlx_string_put(d->mlx, d->win, x, 85, HELP_COLOR,
			"Change Fractal : [1, 2, ...]");
	mlx_string_put(d->mlx, d->win, x, 110, HELP_COLOR,
			"Change Color : [NUM PAD : 1, 2, ...]");
	mlx_string_put(d->mlx, d->win, x, 135, HELP_COLOR,
			"Increase/Decrease current iteration : [+] [-]");
	mlx_string_put(d->mlx, d->win, x, 160, HELP_COLOR,
			"Pause mouse motion : [SPACE]");
	mlx_string_put(d->mlx, d->win, x, 195, HELP_COLOR,
			"Exit : [ESCAPE]");
}
void	settings_background(t_3d *d)
{
	t_index		i;
	unsigned	y_max;
	unsigned	color;

//	color = (d->fractal = BARNSLEY) ? 0x00000000 : BLACK;
	color = 0xaa000000;
	y_max = (d->menu) ? 250 : 45;
	i.y = 0;
	while (i.y < y_max)
	{
		i.x = 0;
		while (i.x < WIDTH)
		{
			mlx_pixel_put(d->mlx, d->win, i.x, i.y, color);
			++i.x;
		}
		++i.y;
//		printf("%f", i.y);
	}
	if (!d->menu)
		mlx_string_put(d->mlx, d->win, 15, 10, HELP_COLOR,
			"Display Menu : Press [H] Button");
	if (d->menu)
		settings(d);
}


// convertir la position x y en position sur le dessin, changer le scale apres le zoom
int		motion_hook(int x, int y, t_3d *d)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && !d->julia_static)
		d->julia = (t_cnb) {.real = (x + d->offset.x) /
			(double)d->zoom + d->max.x, (y + d->offset.y) /
				(double)d->zoom + d->max.y};
	printf("%f\n", d->julia.real);
	printf("%f\n", d->julia.imag);
	fractol(d);
	return (1);
}

int		mouse_scaling_hook(int k, int x, int y, t_3d *d)
{
	if (k == 5 || k == 2)
	{
		d->zoom *= 0.9;
		d->offset.y -= (y + 300 - HEIGHT / 2) * (d->zoom / WIDTH);
		d->offset.x -= (x + 300 - WIDTH / 2) * (d->zoom / HEIGHT);
		if (d->f.max >= 4)
			d->f.max -= 4;
	}
	if (k == 4 || k == 1)
	{
		d->zoom *= 1.1;

		d->offset.y += (y + 250 - HEIGHT / 2) * d->zoom / WIDTH;
		d->offset.x += (x + 250 - WIDTH / 2) * d->zoom / HEIGHT;
		d->f.max += 4;
	}
	fractol(d);
	return (1);
}




