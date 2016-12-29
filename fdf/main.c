/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 07:12:01 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/29 18:26:54 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



/*
** Check for map validity, stock map in d->s and determine max y and max x.
*/
static int		get_x_y(t_3d *d, char *s)
{
	char		*line;
	int			fd;

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
	printf("x : %f\n", d->x);
	printf("y : %f\n", d->y);
	close(fd);
	if (d->x > 1)
		return (1);
	return (d->x ? ft_error("One tile only") : ft_error("Empty file"));
}


/*
** debug function
*/
static int		printmap(t_3d *d)//
{
	int x;
	int y = 0;
	while (y < d->y)
	{
		x = 0;
		while (x < d->x)
		{
			ft_putnbr(d->m[y][x]);
			ft_putstr(" 0x");
			ft_puthex(d->c[y][x++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
		++y;
	}
	return (1);
}

/*
** storing color in d->c
** maybe think to add ishex(char) in the future
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
		return (WHITE);
	d->s = d->s + 2;
	while (*(d->s + n) && (ft_isdigit(*(d->s + n)) || (*(d->s + n) >= 'A' &&
				*(d->s + n) <= 'F')
				|| (*(d->s + n) >= 'a' && *(d->s + n) <= 'f')))
					++n;
	if (!n || !(c = ft_htoi(ft_strndup(d->s, n))))
	{
		d->s += n;
		return (WHITE);
	}
	d->s += n;
	return (c);
}



/*
** Stock int into an array
*/

int			get_depth_and_colors(t_3d *d)
{
	t_xy	i;

	if (!(d->m = (float **)malloc(sizeof(float *) * d->y))
			|| (!(d->c = (int **)malloc(sizeof(int *) * d->y))))
		return (0);
	i.y = 0;
	while (i.y < d->y)
	{
		if (!(d->m[i.y] = (float *)malloc(sizeof(float) * d->x))
				|| (!(d->c[i.y] = (int *)malloc(sizeof(int) * d->x))))
			return (0);
		i.x = 0;
		while (i.x < d->x)
		{
			while (*d->s && *d->s == ' ')
				++d->s;
			d->m[i.y][i.x] = ft_atoi(d->s);
			d->c[i.y][i.x] = get_colors(d);
			++i.x;
		}
		++i.y;
	}
	printmap(d);
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

	d.x = 0;
	d.y = 0;
	if (ac < 2)
		return (ft_error("Usage: ./fdf [File]"));
	if ((fd = open(av[1], O_RDONLY) == -1))
		return (ft_error("Could not open file"));
	if (!(get_x_y(&d, av[1])))
		return (0);
	get_depth_and_colors(&d); // malloc de la map

	//	else if ((fd = open(av[1], O_RDONLY)) == -1)
	//		return (ft_error("Error while opening file"));
	//	else if (close(fd) == -1)
	//	return (ft_error("Error while closing file"));
	//	fdf(ac, av, &d);
	fdf(&d);
	return (0);
}
