/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tetri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 15:38:14 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:53:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains functions related to setting the tetrimino structures.
*/

#include "fillit.h"

/*
** Takes the 2D array of tetriminos and the number of tetriminos, allocates
** memory to and sets the values of the members of each structure, and returns
** an array of t_tetriminos.
** Frees the 2D array.
*/

t_tetrimino	*set_tetriminos(char **ts, short num)
{
	t_tetrimino	*new;
	t_pt		ref;
	short		i;

	if (!(new = ft_memalloc(sizeof(t_tetrimino) * num)))
		return (0);
	i = 0;
	while (ts[i])
	{
		set_reference(ts[i], &ref);
		new[i] = set_points(ts[i], ref);
		new[i].i = i;
		new[i].x = 0;
		new[i].y = 0;
		free(ts[i]);
		i++;
	}
	free(ts);
	return (new);
}

/*
** Takes a string representing a tetrimino and its reference pt.
** Sets the coordinatates of its four points (CHAR_FULL).
** Returns the tetrminino structure.
*/

t_tetrimino	set_points(char *t, t_pt ref)
{
	short		i;
	short		j;
	t_tetrimino	new;

	if (!(new.pts = ft_memalloc(sizeof(t_pt) * 4)))
		return (new);
	i = 0;
	j = 0;
	while (t[i])
	{
		if (t[i] == CHAR_FULL)
		{
			new.pts[j].x = i % T_WIDTH - ref.x;
			new.pts[j].y = i / T_WIDTH - ref.y;
			j++;
		}
		++i;
	}
	return (new);
}

/*
** Sets the coordinatates of the reference point of a tetrminino.
*/

void		set_reference(char *t, t_pt *ref)
{
	short	i;

	ref->x = 100;
	ref->y = 100;
	i = 0;
	while (t[i])
	{
		if (t[i] == CHAR_FULL)
		{
			if (ref->x > i % T_WIDTH)
				ref->x = i % T_WIDTH;
			if (ref->y > i / T_WIDTH)
				ref->y = i / T_WIDTH;
		}
		i++;
	}
}
