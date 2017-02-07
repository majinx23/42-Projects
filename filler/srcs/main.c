/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:11:08 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/07 19:20:11 by angavrel         ###   ########.fr       */
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




