/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 21:07:50 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/10 22:53:03 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** try to put our piece in point (y, x).
** if successful add (save) the point to our list t_point **points
*/

int		put_piece(t_filler *f, BOARD, PIECE, t_point **points)
{
	t_index	i;
	int		success;

	success = 0;
	i.y = 0;
	while (i.y < f->max.y)
	{
		i.x = 0;
		while (i.x < f->max.x)
		{
			if (is_valid_position(f, b, p, i))
			{
				add_point(points, i.y, i.x);
				++success;
			}
			++i.x;
		}
		++i.y;
	}
	return (success ? 1 : 0);
}

/*
** We try to determine is the piece is put in an invalid spot:
** 1) pad.y + i.y >= f->max.y || pad.x + i.x >= f->max.x checks that we don't go
** over the board size.
** 2) if there is already a computer (b[pad.y + i.y][pad.x + i.x] >> 1).
** 3) if there is the player (b[i.y + pad.y][i.x + pad.x] but
** number of connections go beyond 1  && ++connected > 1).
*/

int		is_valid_position(t_filler *f, BOARD, PIECE, t_index i)
{
	t_index	pad;
	int		connected;

	connected = 0;
	pad.y = 0;
	while (pad.y < f->piece_dim.y)
	{
		pad.x = 0;
		while (pad.x < f->piece_dim.x)
		{
			if (p[pad.y][pad.x])
			{
				if (pad.y + i.y >= f->max.y || pad.x + i.x >= f->max.x
				|| (b[pad.y + i.y][pad.x + i.x] >> 1)
				|| (b[i.y + pad.y][i.x + pad.x] && ++connected > 1))
					return (0);
			}
			++pad.x;
		}
		++pad.y;
	}
	return (connected);
}

/*
** save a point inside the list
** create a new one if there was none before, else create a new one at the end
*/

void	add_point(t_point **points, int y, int x)
{
	t_point	*lst;

	if ((lst = *points))
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new_point(y, x);
	}
	else
		*points = new_point(y, x);
}

/*
** function to create a new (x, y) point inside the list
*/

t_point	*new_point(int y, int x)
{
	t_point	*point;

	if (!(point = (t_point *)malloc(sizeof(t_point))))
		return (NULL);
	point->i.y = y;
	point->i.x = x;
	point->next = NULL;
	return (point);
}

/*
** function to free our list once our piece is returned
*/

void	free_saved_positions(t_point **points)
{
	t_point	*lst;
	t_point	*tmp;

	lst = *points;
	while (lst)
	{
		tmp = lst;
		tmp = NULL;
		free(tmp);
		lst = lst->next;
	}
}
