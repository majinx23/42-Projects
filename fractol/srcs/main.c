/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 04:03:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 11:02:12 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

int		main(int ac, char **av)
{
	t_3d	d;

	if (ac != 2 && !usage())
		return (0);
	else if (!(init_variables(&d)))
		return (0);
	init_fractal(&d, av[1]);
	fractol(&d);
	mlx_mouse_hook(d.win, mouse_scaling_hook, &d);
	mlx_hook(d.win, 2, 4, key_hook, &d);
	mlx_hook(d.win, 6, 1 << 8, motion_hook, &d);
	mlx_loop(d.mlx);
	return (0);
}

int	usage(void)
{
	ft_error("Usage: ./fractol <fractal>");
	ft_error("[Mandelbrot] [Julia] [Phoenix]");
	return (0);
}

int		init_variables(t_3d *d)
{

	if (!(d->mlx = mlx_init()))
		ft_error("Mlx initialization failed");
	if (!(d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, TITLE)))
		ft_error("Window creation failed");
	init_img(d);
	if (!d->img)
		ft_error("Image creation failed");
	d->zoom = 200;
	d->color = 0;
	d->menu = 0;
	d->offset = (t_index) {.x = 0, .y = 0};
	d->a = 0;
	return (1);
}

void	init_img(t_3d *d)
{
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;

	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(d->img, &bpp, &sizeline, &endian);
	d->data = data;
	d->bpp = bpp;
	d->sizeline = sizeline;
	d->endian = endian;
}

void	put_pixel_in_img(t_3d *d, int x, int y, int color)
{
	unsigned	octets;
	unsigned	a;
	unsigned	j;

	octets = d->bpp / 8;
	a = x * octets + y * d->sizeline;
	j = 0;
	while (j < octets)
	{
		d->data[a + j] = color;
		color >>= 8;
		++j;
	}
}
