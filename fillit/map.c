/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:44:41 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 15:03:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file includes all the map-related functions.
*/

#include "fillit.h"

/*
** Takes the number of tetriminos present in the input.
** Calculates and returns the smallest size for the square of the map.
*/

short	get_first_size(short nb)
{
	short	result;
	short	nb_cmp;

	nb *= 4;
	result = (nb + 1) / 2 + 1;
	while (--result)
	{
		nb_cmp = result * result;
		if (nb_cmp == nb)
			return (result);
		if (nb_cmp < nb)
			return (result + 1);
	}
	return (0);
}

/*
** Allocates memory to the double int array within the t_map structure and
** sets each int value to 0.
** Initializes other members of the structure: m->size to the size passed as
** parameter, m->i to 0, and m->total to num (the total number of tetriminos we
** have to place).
*/

short	gen_map(t_map *m, short size, short num)
{
	short	i;

	if (!(m->m = (short **)ft_memalloc(sizeof(short *) * size)))
		return (0);
	i = 0;
	while (i < size)
	{
		if (!(m->m[i] = (short *)ft_memalloc(sizeof(short) * size)))
			return (0);
		i++;
	}
	m->size = size;
	m->i = 0;
	m->total = num;
	return (1);
}

/*
** Frees allocated memory within the t_map structure, frees the pointer
** and resets the coordinates of placed tetriminos.
** This function is called on in solve, if fill_map returns 0, ie, when
** the tetriminos cannot be placed in a map of a given size.
*/

void	reset_map(t_map *m, t_tetrimino *ts)
{
	short	i;

	i = 0;
	while (i < m->size)
		free(m->m[i++]);
	free(m->m);
	i = 0;
	while (i < m->total)
	{
		reset_t_coords(ts + i);
		++i;
	}
}

/*
** Allocates memory to a double char array and fills the map with CHAR_EMPTY
** and the tetriminos.
** Returns the two dimensional char array.
*/

char	**get_final_map(t_map *m, t_tetrimino *ts)
{
	char	**result;

	if (!(result = (char **)ft_memalloc(sizeof(char *) * (m->size + 1))))
		return (0);
	m->i = 0;
	while (m->i < m->size + 1)
	{
		if (!(result[m->i] = (char *)ft_memalloc(sizeof(char) * (m->size + 1))))
			return (0);
		ft_memset(result[m->i], CHAR_EMPTY, m->size);
		++m->i;
	}
	m->i = 0;
	while (m->i < m->total)
	{
		set_char(result, ts + m->i);
		++m->i;
	}
	m->i = 0;
	while (m->i < m->total)
		free(ts[m->i++].pts);
	free(ts);
	return (result);
}

/*
** Places each char of a tetrimino of appropriate upper-case letter on the
** final map.
*/

void	set_char(char **result, t_tetrimino *ts)
{
	short	i;

	i = 0;
	while (i < 4)
	{
		result[ts->y + ts->pts[i].y][ts->x + ts->pts[i].x] = ts->i + 65;
		i++;
	}
}
