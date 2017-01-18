/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 04:03:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 09:15:29 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
   Vous devez gérer les conversions suivantes : sSpdDioOuUxXcC
   • Vous devez gérer le %%
   • Vous devez gérer les flags #0-+ et espace
   • Vous devez gérer la taille minimum du champ
   • Vous devez gérer la précision
   • Vous devez gérer les flags hh h l ll j z
   Gestion de conversions plus délicates : eE, fF, gG, aA, n.
   • Gestion de flags plus delicats : *, $, L, ’ .
   • Gestion de flags non existants : %b pour afficher en binaire, %r pour afficher une
   chaine avec des caractères non imprimables, %k pour afficher une date à un format
   ISO quelconque, etc.
   • Gestion de modifieurs pour gérer les couleurs, les fd ou des choses fun comme ça :)
   printf("Le fichier {cyan}%s{eoc} contient : {red}%s{eoc}", filename, str) ;
   */




/*
 *Vous devez fournir un Makefile qui compilera une libftprintf.a. Cette lib sera linké
 à notre main de test pour vous donner votre résultat.
 */


#include "../incl/ft_printf.h"

int		ft_printf(va_start (va_list ap, last))
{
	void va_start(va_list ap, last);

	type va_arg(va_list ap, type);

	void va_copy(va_list dest, va_list src);

	void va_end(va_list ap);
}

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

void	put_pixel_to_img(t_3d *d, int x, int y, int color)
{
	unsigned	octets;
	unsigned	a;
	unsigned	i;

	octets = d->bpp / 8;
	a = x * octets + y * d->sizeline;
	i = 0;
	while (i < octets)
	{
		d->data[a + i] = color;
		color >>= 8;
		++i;
	}
}
