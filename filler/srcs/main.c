/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:11:08 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 17:14:26 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

/*
** launcher and variables initialization
** ./filler_vm -f maps/map00 -p1 players/hcao.filler -p2 ./angavrel.filler
*/

int			main(void)
{
	t_filler	*f;

	f = init_filler();
	parsing(f);
	return (0);
}

/*
** variables initialization
*/

t_filler	*init_filler(void)
{
	t_filler *f;

	if (!(f = (t_filler*)malloc(sizeof(t_filler))))
		return (NULL);
	f->max = (t_index) {.x = 0, .y = 0};
    f->last_p = (t_index) {.y = 7, .x = 2};
	f->board = NULL;
	f->piece= NULL;
	return (f);
}

/*void	print_board(char **board, int max)
{
	int i;

	i = -1;
	while (++i < max)
		ft_putendl(board[i]);
}*/

/*
**	filler_loop
*/

void        filler_loop(t_filler *f)
{
    int        i;
    char    *line;
    char    trash[5];

   
    return_piece(f->max.y, f->max.x);
    get_next_line(0, &line);// skipping 012345...
 //   return_piece(8, 2);
 
    i = -1;
    while (++i < f->max.y)
    {
        read(0, &trash, 4);
        read(0, f->board[i], f->max.x);
        read(0, &trash, 1);
    }
   
    get_next_line(0, &line);//Piece 5 6
    if (!get_piece(f, line))
        ft_error("Wrong piece dimensions");
    i = -1;
   
    f->piece_dim.y = 15;
    while (++i < f->piece_dim.y)
    {
        read(0, f->piece[i], f->piece_dim.x);
        read(0, &trash, 1);
    }
   
    solver(f);
    SKIP_LINE;// skipping plateau..
   // if (1)
    //    filler_loop(filler);  

}

/*

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
**
.*
Player with O: error on input

*/




