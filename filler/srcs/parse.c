/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/07 20:27:14 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

/*
** the fd of GNL is set to 0 as it is where VM sends information.
** compile program and then do one player match
*/

void        parsing(t_filler *f)
{
    char        *line;

 //   SKIP_LINE;//launched ...
    get_next_line(0, &line);//$$$ exec p[1-2]
    f->player = (line[10] - '1') ? 'x' : 'o';
    f->cpu = (f->player == 'x') ? 'o' : 'x';
    get_next_line(0, &line);//Plateau 14 17:  
	      
    get_board_dimension(f, line);
	
    filler_loop(f);
}

/*
** Assuming that VM sends correct data
*/

int		get_board_dimension(t_filler *f, char *s)
{
	int 	i;

	filler_atoi(&f->max, s + 8);
	if (!(f->board = (char **)malloc(sizeof(char *) * (f->max.y + 1))))
		EXIT_MSG("Failed to malloc board dimensions");
	i = -1;
	while (++i < f->max.y)
		if (!(f->board[i] = (char *)malloc(f->max.x + 1)))
			EXIT_MSG("Failed to malloc board dimensions");
	return (1);
}

int		get_piece(t_filler *f, char *s)
{
	int i;

	filler_atoi(&f->piece_dim, s + 6);
	if (!(f->piece = (char **)malloc(sizeof(char *) * (f->piece_dim.y + 1))))
		EXIT_MSG("Failed to malloc piece");
	i = -1;
	while (++i < f->piece_dim.y)
		if (!(f->piece[i] = (char *)ft_memalloc(f->piece_dim.x + 1)))
			EXIT_MSG("Failed to malloc piece");
	return (1);
}

/*
** reset y and x value then
** getting y, skipping the space, getting x.
*/

void	filler_atoi(t_index *i, char *s)
{
	int		r;

	r = 0;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + *s++ - '0';
	i->y = r;
	
	++s;
	r = 0;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + *s++ - '0';
	i->x = r;
	if (i->x <= 0 || i->y <= 0)
		EXIT_MSG("Wrong dimensions");	
}
