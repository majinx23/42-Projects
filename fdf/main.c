/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 07:12:01 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/28 17:30:56 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Check for map validity and determine max y and max x.
*/
static int		get_x_y(t_3d *d, char *s)
{
	char		*line;
	int			fd;

	d->x = 0;
	d->y = 0;
	fd = open(s, O_RDONLY);
	if (get_next_line(fd, &line) == 1)
	{
		d->x = check_validity(line);
		++d->y;
		(line) ? free(line) : 0;
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (d->x != check_validity(line))
			return (ft_error("Invalid file"));
		++d->y;
		(line) ? free(line) : 0;
	}
	printf("x : %f\n", d->x);
	printf("y : %f\n", d->y);
	close(fd);
	if (d->x > 1)
		return (1);
	return (d->x ? ft_error("One tile only") : ft_error("Empty file"));
}

int			get_map_dimension(t_3d *d, char **s)
{
	t_xy	i;
	int		fd;

	i.y = 0;
	i.x = 0;
	if (!(d->m = (float **)malloc(sizeof(float *) * d->y * d->x)))
		return (0);
	fd = open(s, O_RDONLY);
	while (i.y < d->y)
	{
		if (!(d->m[i.y] = (float *)malloc(sizeof(float) * d->x)))
			return (0);
		while (i.x < d->x)
		{
			d->m[i.y][i.x++] = ft_atoi(*s);
			while (*s && (*s != ' ' || *s != '\n'))
				++s;
		}
		d->m[++i.y][i.x];
	}
	close (fd);
	return (1);
}

static void	fdf(t_3d *d)
{
	d->x = 4;
	d->y = sqrt(20);
	d->z = 8;

	d->w = vector_len(d->x, d->y, d->z);
	printf("test function : %f\n", d->w);
}


int			main(int ac, char  **av)
{
	t_3d	d;
	int		fd;

	if (ac < 2)
		return (ft_error("Usage: ./fdf [File]"));
	if ((fd = open(av[1], O_RDONLY) == -1))
		return (ft_error("Could not open file"));
	if (!(get_x_y(&d, av[1])))
		return (0);
	get_map_dimension(&d, av[1]); // malloc de la map

	//	else if ((fd = open(av[1], O_RDONLY)) == -1)
	//		return (ft_error("Error while opening file"));
	//	else if (close(fd) == -1)
	//	return (ft_error("Error while closing file"));
	//	fdf(ac, av, &d);
	fdf(&d);
	return (0);
}
