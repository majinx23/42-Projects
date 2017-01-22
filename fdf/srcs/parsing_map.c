/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:22:17 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 17:04:13 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
** Check for map validity, store map in d->s and determine max y and max x.
*/

int			read_map(t_3d *d, char *s)
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
			d->max.x = parse_map(line);
		}
		else if (d->max.x != parse_map(line))
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
** checks that the map is a valid one with above functions' help
*/

short		parse_map(char *s)
{
	unsigned	i;
	unsigned	x_len;

	i = 0;
	x_len = 0;
	while (s[i] && s[i] != '\n')
	{
		if (ft_isdigit(s[i]))
		{
			if (parse_digit(s, &i) == False)
				return (0);
			++x_len;
		}
		else if (s[i] == '-' && s[i + 1] && ft_isdigit(s[i + 1]))
			++i;
		else if (s[i] == ' ')
			++i;
		else
			return (0);
	}
	return (x_len);
}

/*
** checks that color is valid and stocks it into *d->c
*/

t_bool		parse_color(char *s, unsigned *i)
{
	size_t		n;

	n = 0;
	while (s[*i + n] && (ft_isdigit(s[*i + n]) || (s[*i + n] >= 'A' &&
		s[*i + n] <= 'F') || (s[*i + n] >= 'a' && s[*i + n] <= 'f')))
		++n;
	if (n > 8)
		return (False);
	*i += n;
	return (True);
}

/*
** checks that digit is a valid one.
*/

t_bool		parse_digit(char *s, unsigned *i)
{
	if (!*i || ((s[*i - 1]) == ' ') || (s[*i - 1] == '-'))
		++*i;
	else
		return (False);
	while (s[*i] && ft_isdigit(s[*i]))
		++*i;
	if (s[*i] == ',')
	{
		if (s[*i + 1] && s[*i + 2] && s[*i + 1] == '0' && s[*i + 2] == 'x')
		{
			*i += 3;
			if (parse_color(s, i) == False)
				return (False);
		}
		else
			return (False);
	}
	return (True);
}

/*
** malloc map coordinates, map coordinates modified by matrix and colors.
*/

int			malloc_map(t_3d *d)
{
	t_index		i;

	if (!(d->mm = (t_vector **)malloc(sizeof(t_vector *) * d->max.y))
			|| (!(d->m = (t_vector **)malloc(sizeof(t_vector *) * d->max.y)))
			|| (!(d->c = (int **)malloc(sizeof(int *) * d->max.y))))
		return (0);
	i.y = 0;
	while (i.y < d->max.y)
	{
		if (!(d->mm[i.y] = (t_vector *)malloc(sizeof(t_vector) * d->max.x))
			|| (!(d->m[i.y] = (t_vector *)malloc(sizeof(t_vector) * d->max.x)))
			|| (!(d->c[i.y] = (int *)malloc(sizeof(int) * d->max.x))))
			return (0);
		++i.y;
	}
	return (1);
}
