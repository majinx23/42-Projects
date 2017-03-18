/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reach_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 00:54:16 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/18 18:31:55 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** we try to reach sides depending on starting position
*/

void	has_reached_borders(t_filler *f, BOARD)
{
	t_index		ply_area;

	ply_area = (t_index) {.x = 0, .y = 0};
	if (!f->turn)
	{
		is_disadvantaged(f, b, &ply_area);
		f->goal |= (POSITION == SW || POSITION == SE || POSITION == S) ? 1 : 0;
		f->goal |= (POSITION == NE || POSITION == E || POSITION == SE) ? 2 : 0;
		f->goal |= (POSITION == NW || POSITION == W || POSITION == SW) ? 4 : 0;
		f->goal |= (POSITION == NW || POSITION == NE || POSITION == N) ? 8 : 0;
	}
	if (f->goal & 1)
		if (has_reached_top(f, b))
			f->goal |= ~1;
	if (f->goal & 2)
		if (has_reached_left(f, b))
			f->goal |= ~2;
	if (f->goal & 4)
		if (has_reached_right(f, b))
			f->goal |= ~4;
	if (f->goal & 8)
		if (has_reached_bot(f, b))
			f->goal |= ~8;
}

int		has_reached_top(t_filler *f, BOARD)
{
	t_index	i;

	i.y = 0;
	i.x = 0;
	while (i.x < f->max.x)
	{
		if (b[i.y][i.x] == 1)
			return (1);
		++i.x;
	}
	return (0);
}

int		has_reached_bot(t_filler *f, BOARD)
{
	t_index	i;

	i.y = f->max.y - 1;
	i.x = 0;
	while (i.x < f->max.x)
	{
		if (b[i.y][i.x] == 1)
			return (1);
		++i.x;
	}
	return (0);
}

int		has_reached_left(t_filler *f, BOARD)
{
	t_index	i;

	i.y = 0;
	i.x = 0;
	while (i.y < f->max.y)
	{
		if (b[i.y][i.x] == 1)
			return (1);
		++i.y;
	}
	return (0);
}

int		has_reached_right(t_filler *f, BOARD)
{
	t_index	i;

	i.y = 0;
	i.x = f->max.x - 1;
	while (i.x < f->max.x)
	{
		if (b[i.y][i.x] == 1)
			return (1);
		++i.x;
	}
	return (0);
}
