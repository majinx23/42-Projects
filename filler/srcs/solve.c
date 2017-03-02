/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/02 18:10:34 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

/*
make FLAGS="" re
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
** update_board is a graphic bonus to redraw the mlx
*/

void		solver(t_filler *f, BOARD, PIECE)
{
//	update_board(f, b);
	ft_putstr_fd("\033[32m", 2);
	ft_putstr_fd("~~~ Turn ", 2);
	ft_putnbr_fd(f->turn, 2);
	ft_putstr_fd(" ~~~\n", 2);
	ft_putstr_fd("\033[37m", 2);

	
	shortest_distance(f, b, p);
	LAST.y -= f->min_dim.y;
	LAST.x -= f->min_dim.x;
	return_piece(LAST.y, LAST.x);
	++f->turn;
}


/*
** localize CPU pieces.
** note perso : faire une fonction affine pour voir si ce point proche permet de bloquer
*/

void		shortest_distance(t_filler *f, BOARD, PIECE)
{
	t_index	i;
	f->found = 0;

	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{	
			if (b[i.y][i.x] == CPU)
			{
				C = i;
				player_closest(f, b, p);
			}
		}
	}
}

/*
** localize player pieces and calculate distance to check if it is shorter.
** if the distance is shorter then it tries to put the piece.
*/

int			player_closest(t_filler *f, BOARD, PIECE)
{
	int		tmp;
	t_index	i;

	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{	
			if (b[i.y][i.x] == PLY)
			{
				tmp = (C.x - i.x) * (C.x - i.x) + (C.y - i.y) * (C.y - i.y);	
				if (tmp <= f->distance)
				{
					f->distance = tmp;
					J = i;
					put_piece_on_J(f, b, p);
				}
			}
		}
	}
	return (1);
}

/*
** now that closest point has been localised, we try to put the piece around.
*/

int		put_piece_on_J(t_filler *f, BOARD, PIECE)
{
	int		max_score;

	max_score = 0;
	f->padding.y = 0;
	while ((J.y + f->piece_dim.y - f->padding.y < f->max.y) && 
	(f->padding.y < f->piece_dim.y))
	{
		f->padding.x = 0;
		while ((J.x + f->piece_dim.x - f->padding.x < f->max.x) &&
		(f->padding.x < f->piece_dim.x))
		{
			
			if (piece_valid_position(f, b, p) > max_score)
			{
				max_score = f->score;
				LAST.y = J.y - f->padding.y;
				LAST.x = J.x - f->padding.x;
				f->found = 1;
				return (1);
			}
			++f->padding.x;
		}
		++f->padding.y;
	}
	return (-1);
}

/*
** if number of connections is equal to 2 then piece is invalid in this area.
** it should be connected to only one. kezo rap
*/


int		piece_valid_position(t_filler *f, BOARD, PIECE)
{
	int		connect;
	t_index	i;
	int		cell;
/*
	ft_putstr_fd("Piece [", 2);
	ft_putnbr_fd(f->piece_dim.y, 2);
	ft_putstr_fd("] [", 2);
	ft_putnbr_fd(f->piece_dim.x, 2);
	ft_putstr_fd("]\n", 2);
	ft_putstr_fd("\033[37m", 2);
*/	connect = 0;
	f->score = 0;
	i.y = -1;
	while (++i.y < f->piece_dim.y)
	{
		i.x = -1;
		while (++i.x < f->piece_dim.x)
		{
			if (p[i.y][i.x] == 1)
			{
				cell = b[i.y + J.y - f->padding.y][i.x + J.x - f->padding.x];
				if (cell == 2)
					return (0);
				else if (cell == 1)
				{
					++connect;
					if (connect >= 2)
						return (0);
				}
				else // score will take the area value instead of 
					f->score += cell;
			}
		}
	}
	return (connect);
//	return (connect * f->score); // connect is either equal to 0 or 1.
}





/*
int		try_put_piece_around_J(t_filler *f)
{
	f->padding.y = 0;
	while ((J.y + f->piece_dim.y - f->padding.y < f->max.y) &&
	(f->padding.y < f->piece_dim.y))
	{
		f->padding.x = 0;
		while ((J.x + f->piece_dim.x - f->padding.x < f->max.x) &&
		(f->padding.x < f->piece_dim.x))
		{
			if (try_put_piece(f) == 1)
			{
				LAST.y = J.y - f->padding.y;
				LAST.x = J.x - f->padding.x;
				f->found = 1;
				return (1);
			}
			++f->padding.x;
		}
		++f->padding.y;
	}
	return (-1);
}
*/




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
