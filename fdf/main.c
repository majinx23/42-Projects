/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 07:12:01 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/27 19:18:23 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	x_len(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i++]))
		{
			while (ft_isdigit(s[i]))
				++i;
			++len;
		}
		while (s[i] == ' ')
			++i;
	}
	return (len);
}

int			get_x_y(t_3d *d, char *s)
{
	char	*line;
	int		fd;
	int		check;

	d->x = 0;
	d->y = 0;
	fd = open(s, O_RDONLY);
	if (get_next_line(fd, &line) == 1)
	{
		if (!(check = check_validity(line)))
			return (ft_error("Invalid file"));
		d->x = x_len(line);
		++d->y;
		(line) ? free(line) : 0;
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (check != check_validity(line))
			return (ft_error("Invalid file"));
		++d->y;
		(line) ? free(line) : 0;
	}
	printf("%f\n", d->x);
	printf("%f\n", d->y);
	close(fd);
	return (1);
}

void		get_map_dimension(t_3d *d, char *s)
{
	int		y;
	int		fd;

	y = 0;
	d->m = (double **)malloc(sizeof(double *) * d->y);
	fd = open(s, O_RDONLY);
	//	while (get_next_line(fd, &line) && y < d->y)
	//	{
	//		d->m[y] = (int *)malloc(sizeof(int) * d->x);
	//		++y;
	//	}
	close(fd);
}

static void	fdf(t_3d *d)
{
	d->x = 4;
	d->y = sqrt(20);
	d->z = 8;

	d->w = vector_len(d->x, d->y, d->z);
	printf("%f\n", d->w);
}


int			main(int ac, char  **av)
{
	t_3d	d;
	int		fd;

	if (ac < 2)
		return (ft_error("Usage: ./fdf [File]i\n"));
	if ((fd = open(av[1], O_RDONLY) == -1))
		return (ft_error("Could not open file\n"));
	get_x_y(&d, av[1]); // obtenir x et y
	get_map_dimension(&d, av[1]); // malloc de la map

	//	else if ((fd = open(av[1], O_RDONLY)) == -1)
	//		return (ft_error("Error while opening file"));
	//	else if (close(fd) == -1)
	//	return (ft_error("Error while closing file"));
	//	fdf(ac, av, &d);
	fdf(&d);
	return (0);
}
