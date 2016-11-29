/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:20:24 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:45:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains functions related to manipulating point coordinates.
*/

#include "fillit.h"

/*
** Takes a pointer to a t_tetrimino and resets the coordinates to 0.
*/

void	reset_t_coords(t_tetrimino *ts)
{
	ts->x = 0;
	ts->y = 0;
}

/*
** Increments the coordinates of a tetrimino to be placed.
*/

void	increment_t_coords(t_tetrimino *ts, t_map *m)
{
	if (ts->x == m->size - 1 &&
			ts->y == m->size - 1)
	{
		ts->x = m->size;
		ts->y = m->size;
		return ;
	}
	++ts->x;
	if (ts->x == m->size)
	{
		ts->x = 0;
		++ts->y;
	}
}
