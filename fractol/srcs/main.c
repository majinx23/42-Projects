/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 04:03:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/26 16:49:55 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** main program: Initialize fractals, draw chosen fractal and awaits user input
*/

int		main(int ac, char **av)
{
	t_3d	d;

	if (ac != 2 && !usage())
		return (0);
	else if (!(init_variables(&d)))
		return (0);
	init_fractal(&d, av[1]);
	fractol(&d);
	mlx_mouse_hook(d.img.win, mouse_scaling_hook, &d);
	mlx_hook(d.img.win, 2, 4, key_hook, &d);
	mlx_hook(d.img.win, 6, 1 << 8, motion_hook, &d);
	mlx_loop(d.img.mlx);
	return (0);
}

/*
** Print Usage
*/

int		usage(void)
{
	ft_error("Usage: ./fractol <fractal>");
	ft_error("[Mandelbrot] [Julia] [Phoenix] [Barnsley]");
	return (0);
}

/*
** initialize variables
*/

int		init_variables(t_3d *d)
{
	if (!(d->img.mlx = mlx_init()))
		ft_error("Mlx initialization failed");
	if (!(d->img.win = mlx_new_window(d->img.mlx, WIDTH, HEIGHT, TITLE)))
		ft_error("Window creation failed");
	init_img(d);
	if (!d->img.image)
		ft_error("Image creation failed");
	d->zoom = 200;
	d->color = 0;
	d->menu = 0;
	d->offset = (t_index) {.x = 0, .y = 0};
	d->a = 0;
	return (1);
}

/*
** Initialize image
*/

void	init_img(t_3d *d)
{
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;

	d->img.image = mlx_new_image(d->img.mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(d->img.image, &bpp, &sizeline, &endian);
	d->img.data = data;
	d->img.bpp = bpp;
	d->img.sizeline = sizeline;
	d->img.endian = endian;
}

/*
** Put pixel inside the image
*/

void	put_pixel_in_img(t_3d *d, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		*(int *)&d->img.data[(x * d->img.bpp / 8) +
			(y * d->img.sizeline)] = color;
}
