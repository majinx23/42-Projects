/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/13 08:19:13 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** update_board is a graphic bonus to redraw the mlx
** before returning the piece coordinates (LAST.y LAST.x) we add back the min
** that was initially removed from the piece.
*/

void	solver(t_filler *f, BOARD, PIECE)
{
	t_point	*points;
	t_index	ply_area;
	
	points = NULL;
	ply_area = (t_index) {.x = 0, .y = 0};
	f->cpu_score = 0;
	f->ply_score = 0;
	put_piece(f, b, p, &points);
	if (!points)
		return_piece(-1, -1);
	else
	{
		if (is_disadvantaged(f, b, &ply_area))
			break_through(f, b, points);
		else
			surround(f, b, points);
		return_piece(LAST.y - f->min_dim.y, LAST.x - f->min_dim.x);
		free_saved_positions(&points);
	}
	display_turn_nb(f);//
//	display_last(f);//
//	display_piece(f->piece_dim, p); // debug function
//	display_miniboard(f, f->min_area, f->max_area, b); // debug
	display_board(f->max, b); // debug
}

/*
** main strategy is to surround opponent by finding the shortest distance
** between our saved valid positions and the computer
*/

void	surround(t_filler *f, BOARD, t_point *points)
{
	LAST = points->i;
	while (points)
	{
		if (g_d(f, b, points->i.y, points->i.x) < g_d(f, b, LAST.y, LAST.x))
			LAST = points->i;
		points = points->next;
	}
}

/*
** get_distance
** compare computer location compare to saved points and check if distance is
** closer, if try to put the piece.
** it returns directly distance if equal to 2
*/

int		g_d(t_filler *f, BOARD, int y, int x)
{
	t_index	i;
	int		distance;
	int		tmp;

	distance = f->max.y * f->max.y + f->max.x * f->max.x;
	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{
			tmp = (i.y - y) * (i.y - y) + (i.x - x) * (i.x - x);
			if (b[i.y][i.x] >> 1 && next_to_cpu(f, b, i) && tmp < distance)
				if ((distance = tmp) == 2)
					return (distance);
		}
	}
	return (distance);
}

/*
** absolute priority if piece is close to the cpu
*/

int		next_to_cpu(t_filler *f, BOARD, t_index i)
{
	return ((i.y > 0 && i.y < f->max.y - 1
		&& (b[i.y + 1][i.x] >> 1 || b[i.y - 1][i.x] >> 1))
	|| (i.x > 0 && i.x < f->max.x - 1
		&& (b[i.y][i.x + 1] >> 1 || b[i.y][i.x - 1] >> 1))
	|| (!i.y && b[i.y + 1][i.x] >> 1) || (!i.x && b[i.y][i.x + 1] >> 1)
	|| (i.y == f->max.y - 1 && b[i.y - 1][i.x] >> 1)
	|| (i.x == f->max.x - 1 && b[i.y][i.x - 1] >> 1)
	? 1 : 0);
}
