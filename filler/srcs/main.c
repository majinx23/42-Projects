/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:11:08 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/03 16:17:46 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

t_filler	*init_filler(void)
{
	t_filler *filler;

	if (!(filler = (t_filler*)malloc(sizeof(t_filler))))
		return (NULL);
	filler->player = 0;
	filler->max = (t_index) {.x = 0, .y = 0};
	filler->board = NULL;
	filler->piece= NULL;
	return (filler);
}

/*void	print_board(char **board, int max)
{
	int i;

	i = -1;
	while (++i < max)
		ft_putendl(board[i]);
}*/


void		solver(t_filler *filler)
{
	(void)filler;
}

/*
**	filler_loop
*/

void		filler_loop(t_filler *filler, int do_free)
{
	int		i;
	char	*line;

	i = -1;
	get_next_line(0, &line);// skipping 012345...
	while (++i < filler->max.y)
	{
		(do_free) ? free(filler->board[i]) : 0;
		get_next_line(0, &filler->board[i]);
	}
	i = -1;
	while (++i < filler->max.y)
	{
		(do_free) ? free(filler->board[i]) : 0;
		get_next_line(0, &filler->board[i]);
	}
	solver(filler);
	get_next_line(0, &line);// skipping plateau..
	if (line[0] != '=')
		filler_loop(filler, 1);
	return ;
}


/*
** the fd of GNL is set to 0 as it is where VM sends information.
** compile program and then do one player match
*/

void		parsing(t_filler *filler)
{
	char		*line;

	printf("START PARSING\n");
	SKIP_LINE;
	get_next_line(0, &line);
	filler->player = line[10] - '0';
	filler->letter = (filler->player == 1) ? 'o' : 'x';
	if (P == 1)
	{
		SKIP_LINE;
		SKIP_LINE;
	}
	get_next_line(0, &line);
	if (!(get_board_dimension(filler, line)))
		ft_error("Wrong map dimensions");
	printf("ahah\n");
	printf("%i %c %d %d %d %d\n", P, L, filler->max.y, filler->max.x, filler->piece_dim.y, filler->piece_dim.x);

	filler_loop(filler, 0);
//	print_board(filler->board, filler->max.y);
	return ;
}

/*
** launcher and variables initialization
** ./filler_vm -f maps/map00 -p1 players/hcao.filler -p2 ./angavrel.filler
*/

int			main(void)
{
	t_filler	*filler;

	filler = init_filler();
//	ft_putendl_fd("angavrel.filler", 0);
	parsing(filler);
	return (0);
}
