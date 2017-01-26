/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 05:55:43 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/26 18:14:09 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

static void		settings(t_3d *d, unsigned color)
{
	short		x;

	x = 15;
	mlx_string_put(d->img.mlx, d->img.win, x, 10, color,
			"Press 'H' to close help");
	mlx_string_put(d->img.mlx, d->img.win, x, 35, color,
			"West, East, North, South : [<-] [->] [^] [v]");
	mlx_string_put(d->img.mlx, d->img.win, x, 60, color,
			"Zoom : [Mouse wheel or right/left click]");
	mlx_string_put(d->img.mlx, d->img.win, x, 85, color,
			"Change Fractal : [1, 2, ...]");
	mlx_string_put(d->img.mlx, d->img.win, x, 110, color,
			"Change Color : [NUM PAD : 1, 2, ...]");
	mlx_string_put(d->img.mlx, d->img.win, x, 135, color,
			"Increase/Decrease current iteration : [+] [-]");
	mlx_string_put(d->img.mlx, d->img.win, x, 160, color,
			"Pause mouse motion : [SPACE]");
	mlx_string_put(d->img.mlx, d->img.win, x, 195, color,
			"Exit : [ESCAPE]");
}

void		settings_background(t_3d *d)
{
	t_index		i;
	unsigned	y_max;
	unsigned	color;

	y_max = (d->menu) ? 230 : 45;
	i.y = 0;
	color = 0xaa000000;
	while (i.y < y_max)
	{
		i.x = 0;
		while (i.x < WIDTH)
		{
			mlx_pixel_put(d->img.mlx, d->img.win, i.x, i.y, color);
			++i.x;
		}
		++i.y;
	}
	if (!d->menu)
		mlx_string_put(d->img.mlx, d->img.win, 15, 10, HELP_COLOR,
			"Display Menu : Press [H] Button");
	if (d->menu)
		settings(d, HELP_COLOR);
}

/*
** change julia's real number based on mouse position
*/

int			motion_hook(int x, int y, t_3d *d)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && !d->julia_static)
		d->julia = (t_cnb) {.real = (x + d->offset.x) /
			(double)d->zoom + d->max.x, (y + d->offset.y) /
				(double)d->zoom + d->max.y};
//	printf("%f\n", d->julia.real);//
//	printf("%f\n", d->julia.imag);//
	fractol(d);
	return (1);
}

/*
** zooming function
*/

int			mouse_scaling_hook(int k, int x, int y, t_3d *d)
{
	/*
	if (k == 5 || k == 2)
	{
		d->zoom *= 0.8;
		d->offset.y = (y - d->offset.y - HEIGHT / 2) * (d->zoom / HEIGHT);
		d->offset.x = (x - d->offset.x - WIDTH / 2) * (d->zoom / WIDTH);
		if (d->f.max >= 4)
			d->f.max -= 4;
	}
	if (k == 4 || k == 1)
	{
		d->zoom *= 1.25;
		d->offset.y -= (y - HEIGHT / 2) * (d->zoom / HEIGHT);
		d->offset.x -= (x - WIDTH / 2) * (d->zoom / WIDTH);
		d->f.max += 4;
		printf("offset : (%f, %f)\n", d->offset.x, d->offset.y);
	}*/
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (k == 4 || k == 1)
		{ //H800 W900
			
			d->zoom *= 1.25;
			d->offset.x = round(x - ((WIDTH / 2 + d->offset.x)) * 0.8);
			d->offset.y = round(y - ((HEIGHT / 2 + d->offset.y)) * 0.8);
			printf("on clique en [%d, %d]\n, offset : (%f, %f)\n", x, y, d->offset.x, d->offset.y);
		}
	}
	fractol(d);
	
	return (1);
}
