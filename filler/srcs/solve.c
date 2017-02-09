/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/09 22:10:41 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"
/*
int			put_piece(t_filler *f)
{
	t_index	i;

	i.y = LAST.y;
	while (i.y < f->max.y)
	{
		i.x = LAST.x;
		while (i.x < f->max.x)
		{
			
			++i.x;
		}
		++i.y;
	}
	return (1);
}

*/


/*
make re
time ./angavrel.filler
$$$ exec p2 : [players/superjeannot.filler]
Plateau 15 17:
01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 2 2:
*.
*.

*/


/*
** if number of connections is equal to 2 then piece is invalid in this area.
** it should be connected to only one.
*/

int		try_put_piece(t_filler *f)
{
	int		connect;
	t_index	i;

	connect = 0;
	i.y = -1;
	while (++i.y < f->piece_dim.y)
	{
		i.x = -1;
		while (++i.x < f->piece_dim.x)
		{
			if ((f->b[i.y + J.y - f->padding.y][i.x + J.x - f->padding.x]
			+ f->p[i.y][i.x]) == 3)
				return (-1);
			else if (f->b[i.y + J.y - f->padding.y][i.x + J.x - f->padding.x] == 1
			&& f->p[i.y][i.x] == 1)
			{
				++connect;
				if (connect >> 2)
					return (-1);
			}
		}
	}
	return ((!connect) ? -1 : 1);
}

/*
** now that closest point has been localised, we try to put the piece around.
*/

int		try_put_piece_around_J(t_filler *f)
{
	while ((J.y + f->piece_dim.y - f->padding.y < f->max.y) &&
	(f->padding.y < f->piece_dim.y))
	{
		f->padding.x = 0;
		while ((J.x + f->piece_dim.x - f->padding.x < f->max.x) &&
		(f->padding.x < f->piece_dim.x))
		{
			if (try_put_piece(f) == 1)
			{
				LAST = J;
				return (1);
			}
			++f->padding.x;
		}
		++f->padding.y;
	}
	return (-1);
}

/*
** localize player pieces and calculate distance to check if it is shorter.
** if the distance is shorter then it tries to put the piece.
*/

void		player_closest(t_filler *f)
{
	int		tmp;
	t_index	i;

	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{	
			if (f->b[i.y][i.x] == PLY)
			{
				tmp = (C.x - i.x) * (C.x - i.x) + (C.y - i.y) * (C.y - i.y);	
				if (tmp < f->distance)
				{
					f->distance = tmp;
					J = i;
					f->padding = (t_index) {.y = 0, .x = 0};
					try_put_piece_around_J(f);
				}
			}
		}
	}
}

/*
** localize CPU pieces.
*/

void		shortest_distance(t_filler *f)
{
	t_index	i;

	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{	
			if (f->b[i.y][i.x] == CPU)
			{
				C = i;
				player_closest(f);
			}
		}
	}
}



void		solver(t_filler *f)
{
	shortest_distance(f);
	return_piece(LAST.y, LAST.x);
}

/*
** returns to cpu coordinates chosen to put piece
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
