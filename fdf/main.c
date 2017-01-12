/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 07:12:01 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/12 23:52:40 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Check for map validity, store map in d->s and determine max y and max x.
*/
static int		get_x_y(t_3d *d, char *s)
{
	char	*line;
	int		fd;

	fd = open(s, O_RDONLY);
	if (get_next_line(fd, &line) == 1)
	{
		d->s = ft_strdup(line);
		d->x = check_validity(line);
		++d->y;
		(line) ? free(line) : 0;
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (d->x != check_validity(line))
			return (ft_error("Invalid file"));
		d->s = ft_strjoin(d->s, " ");
		d->s = ft_strjoin(d->s, line);
		++d->y;
		(line) ? free(line) : 0;
	}
	close(fd);
	if (d->x > 1)
		return (1);
	return (d->x ? ft_error("One tile only") : ft_error("Empty file"));
}


/*
** debug function

static int		printmap(t_3d *d)//
{
	unsigned x;
	unsigned y = 0;
	while (y < d->y)
	{
		x = 0;
		while (x < d->x)
		{
			ft_putnbr(d->m[y][x]);
			ft_putstr(" 0x");
			ft_puthex(d->c[y][x]);
			ft_putchar(' ');
			++x;
		}
		ft_putchar('\n');
		++y;
	}
	return (1);
}
*/
/*
** storing color in d->c
** maybe think to add ishex(char) in the future
** we put def_color.x equal to 1 to indicate that we will use color provided
** by the map instead of our own colors.
*/
static	int		get_colors(t_3d *d)
{
	size_t	n;
	int		c;

	n = 0;
	if (*d->s == '-')
		++d->s;
	while (ft_isdigit(*d->s))
		++d->s;
	if (*(d->s) == ' ')
		return (0xffffff);
	d->s = d->s + 2;
	while (*(d->s + n) && (ft_isdigit(*(d->s + n)) || (*(d->s + n) >= 'A' &&
				*(d->s + n) <= 'F')
				|| (*(d->s + n) >= 'a' && *(d->s + n) <= 'f')))
					++n;
	if (!n || !(c = ft_htoi(ft_strndup(d->s, n))))
	{
		d->s += n;
		return (0xffffff);
	}
	d->s += n;
	return (c);
}

/*
** offs.y is margin from highest point and offs.x margin from lowest point
*/
static	void	get_window_w_and_h(t_3d *d)
{
	t_xy	i;

	i.y = 0;
	d->offs.y = 0;
	d->offs.x = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
			if (d->offs.y < d->m[i.y][i.x].z - i.x / 2)
				d->offs.y = d->m[i.y][i.x].z - i.x / 2;
			if (d->offs.x < d->m[i.y][i.x].z + i.y / 2)
				d->offs.x = d->m[i.y][i.x].z + i.y / 2;
			++i.x;
		}
		++i.y;
	}
	d->dimension.y = 8 * (d->offs.x - d->offs.y) * 3.6;
	d->dimension.x = 8 * 1.2 * (d->x + d->y);
}

/*
** Store z and colors into an array
*/

int				get_depth_and_colors(t_3d *d)
{
	t_index	i;
	d->z_min = 0;
	d->z_max = 0;

	if (!(d->m = (t_vector **)malloc(sizeof(t_vector *) * d->y))
			|| (!(d->c = (int **)malloc(sizeof(int *) * d->y))))
		return (0);
	i.y = -1;
	while (++i.y < d->y && (i.x = -1) != 0)
	{
		if (!(d->m[i.y] = (t_vector *)malloc(sizeof(t_vector) * d->x))
				|| (!(d->c[i.y] = (int *)malloc(sizeof(int) * d->x))))
			return (0);
		while (++i.x < d->x)
		{
			while (*d->s && *d->s == ' ')
				++d->s;
			d->m[i.y][i.x].z = ft_atoi(d->s);
			d->m[i.y][i.x].y = i.y;
			d->m[i.y][i.x].x = i.x;
			d->m[i.y][i.x].z > d->z_max ? d->z_max = d->m[i.y][i.x].z : 0;
			d->m[i.y][i.x].z < d->z_min ? d->z_min = d->m[i.y][i.x].z : 0;
			d->c[i.y][i.x] = get_colors(d);
		}
	}
//	printmap(d);
	return (1);
}

/*
** Main function
*/
int				main(int ac, char  **av)
{
	t_3d	d;
	int		fd;

	d.x = 0;
	d.y = 0;
	if (ac < 2)
		return (ft_error("Usage: ./fdf [File]"));
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ft_error("Could not open file"));
	if (!get_x_y(&d, av[1]) || !get_depth_and_colors(&d))
		return (ft_error("Malloc failed"));
	get_window_w_and_h(&d);
	init_variables(&d);
	d.mlx = mlx_init();
	if (!(d.w = mlx_new_window(d.mlx, d.dimension.x, d.dimension.y, TITLE)))
		return (ft_error("Window's creation failed"));
	if (!malloc_map(&d))
				return (ft_error("Conversion to isometric 3d failed"));
	color_map(&d);
	fdf(&d);
	return (0);
}
