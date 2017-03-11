/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/11 05:35:05 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

/*
** update_board is a graphic bonus to redraw the mlx
** before returning the piece coordinates (LAST.y LAST.x) we add back the min
** that was initially removed from the piece.
*/

void	solver(t_filler *f, BOARD, PIECE)
{
	t_point	*points;
	
//	update_board(f, b);
	points = NULL;

	put_piece(f, b, p, &points);
	if (!points)
		return_piece(-1, -1);
	else
	{
		surround(f, b, points);
		return_piece(LAST.y - f->min_dim.y, LAST.x - f->min_dim.x);
		free_saved_positions(&points);
	}
//	display_turn_nb(f);//
//	display_last(f);//
//	display_piece(f->piece_dim, p); // debug function
//	display_board(f->max, b); // debug
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

/*
** returns to cpu coordinates chosen to put piece
** I did this before ft_printf was done :X ...
*/

void	return_piece(int a, int b)
{
	char	*s;
	t_index	tmp;
	t_index	i;

	tmp.x = a;
	tmp.y = b;
	i.x = (a < 0) ? 2 : 1;
	i.y = (b < 0) ? 2 : 1;
	while ((tmp.x /= 10) >= 1)
		++i.x;
	while ((tmp.y /= 10) >= 1)
		++i.y;
	if (!(s = (char*)malloc(sizeof(char) * (i.x + i.y + 3))))
		return ;
	s[i.x] = ' ';
	s[i.x + i.y + 1] = '\n';
	s[i.x + i.y + 2] = '\0';
	while (i.y-- && (s[i.x + 1 + i.y] = b % 10 + '0'))
		b /= 10;
	while (i.x-- && (s[i.x] = a  % 10 + '0'))
		a /= 10;
	ft_putstr(s);
	free(s);
}
