/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/11 05:03:05 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

/*
** function to trim piece
** --f->min_dim.x; is to convert the dimension into index
** if the minimum index of y or x is different from 0 
** then we will trim our piece
*/

void	get_piece_dimension(t_filler *f, char *line, BOARD)
{
	int		p[f->piece_dim.y][f->piece_dim.x];
	t_index	i;

	i.y = -1;
    while (++i.y < f->piece_dim.y)
	{
		get_next_line(0, &line);
		i.x = -1;
		while (++i.x < f->piece_dim.x)
			p[i.y][i.x] = INT2(line[i.x]);
	}
	f->min_dim = (t_index) {.x = 1, .y = 1};
	while (!check_min(f, f->piece_dim.y, f->min_dim.x, p))
		++f->min_dim.x;
	--f->min_dim.x;
	while (!check_min(f, f->min_dim.y, f->piece_dim.x, p))
		++f->min_dim.y;
	--f->min_dim.y;
	if (f->min_dim.y || f->min_dim.x)
		trim_piece(f, p);
	solver(f, b, p);
}

/*
** check useful rows and columns
*/

int		check_min(t_filler *f, int y, int x, PIECE)
{
	t_index	i;
	int		n;

	n = 0;
	i.y = 0;
	while (i.y < y)
	{
		i.x = 0;
		while (i.x < x)
		{
			n += p[i.y][i.x];
			++i.x;
		}
		++i.y;
	}
	return (n);
}

/*
** trim piece by removing extra rows and columns from TOKEN
*/

void	trim_piece(t_filler *f, PIECE)
{
	t_index		i;

	i.y = -1;
	while (++i.y < f->piece_dim.y - f->min_dim.y)
	{
		i.x = -1;
		while (++i.x < f->piece_dim.x - f->min_dim.x)
		{
			p[i.y][i.x] = p[i.y + f->min_dim.y][i.x + f->min_dim.x];
			p[i.y + f->min_dim.y][i.x + f->min_dim.x] = 0;
		}
	}
}

/*
** function to reset y and x values then
** getting y, skipping the space, getting x.
*/

void	filler_atoi(t_index *max, char *s)
{
	int		r;

	r = 0;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + *s++ - '0';
	max->y = r;
	++s;
	r = 0;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + *s++ - '0';
	max->x = r;
	if (max->x <= 0 || max->y <= 0)
		EXIT_MSG("Wrong dimensions");	
}
