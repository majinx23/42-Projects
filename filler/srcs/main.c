/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:11:08 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/29 00:16:51 by angavrel         ###   ########.fr       */
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

int	get_player_position(char *s)
{
	if (s[1] == '}')  // flags
		return (0);
	return (1);
}


void	print_board(char **board, int max)
{
	int i;

	i = -1;
	while (++i < max)
		ft_putendl(board[i]);
}

/*
** the fd of GNL is set to 0 as it is where VM sends information.
** compile program and then do one player match
*/

void	filler(t_filler *filler)
{
	char		*line;
	int			line_index;
	int			i;

	line_index = 0;
	i = 0;
	printf("%s", "gagaga");
	while (get_next_line(0, &line) == 1)
	{
		if (line_index == 5 || line_index == 7)
		{
			if (!(filler->player = get_player_position(line)))
				ft_error("Wrong play name");
		}
		else if (line_index == 9)
		{
			if (!(get_board_dimension(filler, line)))
				ft_error("Wrong map dimensions");
		}
		else if (line_index > 10 && i < filler->max.y)
		{
			line += 3;
			filler->board[i] = ft_strndup(line, filler->max.x); // should remove \n
		}
		else if (line_index > (10 + filler->max.y))
			;//get_piece(filler, line); // check piece dimension
		++line_index;
		printf("%s", line);
	}
	print_board(filler->board, filler->max.y);
	return (0);
}


int			main(void)
{
	t_filler	filler;

	filler = init_filler();
	filler(&filler);
	return (0);
}
