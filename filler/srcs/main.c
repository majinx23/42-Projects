/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:11:08 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/03 20:19:57 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

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

void        filler_loop(t_filler *filler)
{
    int        i;
    char    *line;
    char    trash[5];

    get_next_line(0, &line);// skipping 012345...
    i = -1;
    filler->max.y = 15;
    while (++i < filler->max.y)
    {
        read(0, &trash, 4);
        read(0, filler->board[i], filler->max.x);
        read(0, &trash, 1);
    }
    
    get_next_line(0, &line);//Piece 5 6
    if (!get_piece(filler, line))
        ft_error("Wrong piece dimensions");
    i = -1;
    filler->piece_dim.y = 15;
    while (++i < filler->piece_dim.y)
    {
        read(0, filler->piece[i], filler->piece_dim.x);
        read(0, &trash, 1);
    }
    solver(filler);
//    SKIP_LINE;// skipping plateau..
//    if (line[0] != '=')
//        filler_loop(filler);
    return ;
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

/*
** the fd of GNL is set to 0 as it is where VM sends information.
** compile program and then do one player match
*/

void        parsing(t_filler *f)
{
    char        *line;


    SKIP_LINE;//launched ...
    get_next_line(0, &line);//$$$ exec p[1-2]
    f->player = (line[10] - '1') ? 'x' : 'o';
    f->cpu = (f->player == 'x') ? 'o' : 'x';
    get_next_line(0, &line);//Plateau 14 17:
    if (!get_board_dimension(f, line))
        ft_error("Wrong board dimensions");
    filler_loop(f);
    return ;
}


/*
** launcher and variables initialization
** ./filler_vm -f maps/map00 -p1 players/hcao.filler -p2 ./angavrel.filler
*/

int			main(void)
{
	t_filler	*f;
	FILE *fp;

   fp = fopen("test.txt", "w+");
   fprintf(fp, "This is testing for fprintf...\n");
   fputs("This is testing for fputs...\n", fp);
   fclose(fp);

	f = init_filler();
//	ft_putendl_fd("angavrel.filler", 0);
	parsing(f);
	return (0);
}
