/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 05:38:00 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/11 05:38:02 by angavrel         ###   ########.fr       */
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
	t_env		env;
    char        *line;

	ft_bzero(&env, sizeof(t_env));
	f.env = &env;
    get_next_line(0, &line);
	f.player = (line[10] - '1') ? 2 : 1;
	f.cpu = (f.player >> 1) ? 1 : 2;
    get_next_line(0, &line);
	f.max = (t_index) {.y = 0, .x = 0};      
  	filler_atoi(&f.max, line + 8);
//	ft_init_win(f.env, f.max);
	f.turn = 0;
	while (1)
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
        get_next_line(0, &line);
		board_char2int(f, line + 4, i.y, b);
	}
//	board_char2int(PLY, f->max, b);
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
		if (s[x] == 'o' || s[x] == 'O')
			b[y][x] = PLY;
		else if (s[x] == 'x' || s[x] == 'X')
			b[y][x] = (PLY - 1);
}
