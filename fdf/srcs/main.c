/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 07:12:01 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 15:25:02 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
** Check for map validity, store map in d->s and determine max y and max x.
*/

static int		get_x_y(t_3d *d, char *s)
{
	char	*line;
	int		fd;

	fd = open(s, O_RDONLY);
	d->max.x = -1;
	while (get_next_line(fd, &line) == 1)
	{
		if (d->max.x == -1)
		{
			d->s = ft_strdup(line);
			d->max.x = check_validity(line);
		}
		else if (d->max.x != check_validity(line))
			return (ft_error("Invalid file"));
		d->s = (d->max.x != -1) ? ft_strjoinfree(d->s, " ", 'L') : d->s;
		d->s = (d->max.x != -1) ? ft_strjoinfree(d->s, line, 'B') : d->s;
		++d->max.y;
	}
	close(fd);
	free(line);
	if (d->max.x > 1)
		return (1);
	return (d->max.x ? ft_error("One tile only") : ft_error("Empty file"));
}

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
	d->season = 1;
	return (c);
}

/*
** Store z and colors into an array
*/

int				get_depth_and_colors(t_3d *d)
{
	t_index		i;
	
	d->z_min = 0;
	d->z_max = 0;
	if (!(d->m = (t_vector **)malloc(sizeof(t_vector *) * d->max.y))
			|| (!(d->c = (int **)malloc(sizeof(int *) * d->max.y))))
		return (0);
	i.y = -1;
	while (++i.y < d->max.y && (i.x = -1) != 0)
	{
		if (!(d->m[i.y] = (t_vector *)malloc(sizeof(t_vector) * d->max.x))
				|| (!(d->c[i.y] = (int *)malloc(sizeof(int) * d->max.x))))
			return (0);
		while (++i.x < d->max.x)
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
	return (1);
}

/*
** Main function parsing before caling fdf
*/

int				main(int ac, char  **av)
{
	t_3d	d;
	int		fd;

	if (ac < 2)
		return (ft_error("Usage: ./fdf [File]"));
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ft_error("Could not open file"));
	d.help_display = 2;
	if (!get_x_y(&d, av[1]) || !get_depth_and_colors(&d))
		return (ft_error("Malloc failed"));
	init_variables(&d);
	d.img.mlx = mlx_init();
	if (!(d.img.w = mlx_new_window(d.img.mlx, WIDTH, HEIGHT, TITLE)))
		return (ft_error("Window's creation failed"));
	if (!malloc_map(&d))
		return (ft_error("Conversion to isometric 3d failed"));
	if (d.season != 4)
		color_map(&d);
	d.vertical_view = 0;
	fdf(&d);
	return (0);
}
