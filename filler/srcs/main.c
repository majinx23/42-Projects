/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 05:38:00 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/17 23:03:40 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** the fd of GNL is set to 0 as it is where VM sends information.
** compile program and then do one player match
** f->cpu = (f->player >> 1) equivalent to f->cpu = (f->player == 2)
** first get_next_line is for //$$$ exec p[1-2]
** second one is for //Plateau 14 17:
*/

int			main(void)
{
	t_filler	f;
    char        *line;

	system("> board.map");
    get_next_line(0, &line);
	f.player = line[10] - '0';
	f.cpu = (f.player & 2) >> 1 | (f.player & 1) << 1;
    get_next_line(0, &line);
	f.max = (t_index) {.y = 0, .x = 0};      
  	filler_atoi(&f.max, line + 8);
	f.turn = 0;
	while (f.turn < 200)// 1
	    filler_loop(&f);
	return (0);
}


/*
** first SKIP_LINE is used in order to skip "012345..."
** then we store into an array data related to the board shape
** second SKIP_LINE is to get piece dimensions (Piece 5 6)
** then we store into an array data related to the piece shape
** third SKIP_LINE is to skip Plateau as we already know board dimensions
*/

void        filler_loop(t_filler *f)
{
    t_index	i;
    char    *line;
	int		b[f->max.y][f->max.x];

    SKIP_LINE;
    i.y = -1;
    while (++i.y < f->max.y)
	{
		if (get_next_line(0, &line) == -1)
		{
			ft_error("GNL Error");
			exit(1);
		}
		board_char2int(f, line + 4, i.y, b);
	}
	check_min_area(f, b);
	check_max_area(f, b);
    SKIP_LINE;
	f->piece_dim = (t_index) {.y = 0, .x = 0};
	filler_atoi(&f->piece_dim, line + 6);
	get_piece_dimension(f, line, b);
    SKIP_LINE;
}

/*
** function to convert the board into ints :
** 1 for Player and 2 for CPU, 0 if empty.
*/

void	board_char2int(t_filler *f, char *s, int y, BOARD)
{
	int	x;

	x = -1;
	while (s[++x])
		if (s[x] == 'O')
			b[y][x] = PLY;
		else if (s[x] == 'X')
			b[y][x] = (PLY & 2) >> 1 | (PLY & 1) << 1;
		else
			b[y][x] = 0;
}

/*
** function to check trimmed board limits (min point and max point)
*/

void	check_min_area(t_filler *f, BOARD)
{
	t_index	i;

	i.y = -1;
	f->min_area.y = -1;
	while (++i.y < f->max.y && f->min_area.y == -1)
	{
		i.x = -1;
		while (++i.x < f->max.x && f->min_area.y == -1)
		{
			if (b[i.y][i.x])
				f->min_area.y = i.y;
		}
	}
	f->min_area.x = -1;
	i.x = -1;
	while (++i.x < f->max.x && f->min_area.x == -1)
	{
		i.y = -1;
		while (++i.y < f->max.y && f->min_area.x == -1)
		{
			if (b[i.y][i.x])
				f->min_area.x = i.x;
		}
	}
}

void	check_max_area(t_filler *f, BOARD)
{
	t_index	i;

	i.y = f->max.y;
	f->max_area.y = -1;
	while (--i.y >= 0 && f->max_area.y == -1)
	{
		i.x = f->max.x;
		while (--i.x >= 0 && f->max_area.y == -1)
		{
			if (b[i.y][i.x])
				f->max_area.y = i.y;
		}
	}
	f->max_area.x = -1;
	i.x = f->max.x;
	while (--i.x >= 0 && f->max_area.x == -1)
	{
		i.y = f->max.y;
		while (--i.y >= 0 && f->max_area.x == -1)
		{
			if (b[i.y][i.x])
				f->max_area.x = i.x;
		}
	}
}
