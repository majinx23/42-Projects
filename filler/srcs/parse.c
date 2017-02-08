/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/08 19:34:57 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

/*
** the fd of GNL is set to 0 as it is where VM sends information.
** compile program and then do one player match
*/

int			main(void)
{
	t_filler	*f;
    char        *line;

	f = init_filler();
    get_next_line(0, &line);//$$$ exec p[1-2]
    f->player = (line[10] - '1') ? 'X' : 'O';
    f->cpu = (f->player == 'X') ? 'O' : 'X';
    get_next_line(0, &line);//Plateau 14 17:       
    get_board_dimension(f, line);
    filler_loop(f);
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
    LAST = (t_index) {.y = 8, .x = 2};
	f->cpu_closest_piece = (t_index) {.y = 0, .x = 0};
	f->board = NULL;
	f->piece= NULL;
	f->distance = 2147483647;
	return (f);
}

void        filler_loop(t_filler *f)
{
    int        i;
    char    *line;

    SKIP_LINE;                        //skipping 012345...
    i = -1;
    while (++i < f->max.y)            //on lit et passe le tableau
    {
        get_next_line(0, &f->board[i]);
        ft_putstr_fd("\033[32m", 2);
        ft_putendl_fd(f->board[i], 2);
        ft_putstr_fd("\033[37m", 2);
    }
    free(line);

    get_next_line(0, &line);        //Piece 5 6
    get_piece(f, line);
    i = -1;
    while (++i < f->piece_dim.y)    //on lit et passe la piece
    {
        get_next_line(0, &f->piece[i]);
   //     ft_putstr_fd("\033[33m", 2);
     //   ft_putendl_fd(f->piece[i], 2);
       // ft_putstr_fd("\033[37m", 2);
    }
	
    free(line);
    solver(f);
    SKIP_LINE;                        // skipping plateau..
	
	if (i != -1)
    	filler_loop(f);
	else
	{
		i = -1;
	    while (++i < f->piece_dim.y)    //on lit et passe la piece
    		free(f->piece[i]);
	}
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
		if (!(f->board[i] = (char *)malloc(3 + f->max.x + 1)))
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
