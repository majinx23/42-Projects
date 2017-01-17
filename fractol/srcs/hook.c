/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 05:55:43 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/17 15:27:37 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

static void	menu_background(t_3d *d)
{
	t_index		i;
	t_index		max;
	unsigned	menu_background_color;

	menu_background_color = 0x20;
	if (!d->menu)
		max = (t_index) {.x = 250, .y = 50};
	else
		max = (t_index) {.x = 420, .y = 200};
	i.y = 0;
	while (i.y < max.y)
	{
		i.x = 0;
		while (i.x < max.x)
		{
			mlx_pixel_put(d->mlx, d->win, i.x, i.y, menu_background_color);
			++i.x;
		}
		++i.y;
	}
}

void		menu(t_3d *d)
{
	unsigned	menu_color;
	short		x;

	x = 15;
	menu_color = TEAL;
	menu_background(d);
	if (!d->menu)
		mlx_string_put(d->mlx, d->win, x, 15, menu_color,
				"Display Menu : Press [H] Button");
	else
	{
		mlx_string_put(d->mlx, d->win, x, 15, menu_color,
				"Press 'h' to close help");
		mlx_string_put(d->mlx, d->win, x, 40, menu_color,
				"West, East, North, South : [<-] [->] [^] [v]");
		mlx_string_put(d->mlx, d->win, x, 65, menu_color,
				"Zoom : [Mouse wheel or right/left click]");
		mlx_string_put(d->mlx, d->win, x, 90, menu_color,
				"Change Fractal : [1, 2, ...]");
		mlx_string_put(d->mlx, d->win, x, 115, menu_color,
				"Change Color : [NUM PAD : 1, 2, ...]");
		mlx_string_put(d->mlx, d->win, x, 140, menu_color,
				"Increase/Decrease current iteration : [+] [-]");
		mlx_string_put(d->mlx, d->win, x, 165, menu_color,
				"Pause mouse motion : [SPACE]");
		mlx_string_put(d->mlx, d->win, x, 165, menu_color,
				"Exit : [ESCAPE]");
	}
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




