/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/09 22:45:38 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

/*
** the fd of GNL is set to 0 as it is where VM sends information.
** compile program and then do one player match
** f->cpu = (f->player >> 1) equivalent to f->cpu = (f->player == 2) 
*/

int			main(void)
{
	t_filler	*f;
    char        *line;

	f = init_filler();
    get_next_line(0, &line);//$$$ exec p[1-2]
//   f->player = (line[10] - '1') ? 'X' : 'O';
//   f->cpu = (f->player == 'X') ? 'O' : 'X';
	PLY = (line[10] - '1') ? 2 : 1;
	CPU = (f->player >> 1) ? 1 : 2;
//	ft_putnbr_fd(PLY, 2);
//	ft_putnbr_fd(CPU, 2);
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
	f->turn = 0;
	return (f);
}

/*
** function to convert the board into ints :
** 1 for Player and 2 for CPU, 0 if empty.
*/

void	board_char2int(t_filler *f)
{
	t_index	i;

	i.y = -1;
    while (++i.y < f->max.y)
    {
		i.x = -1;
		while (++i.x < f->max.x)
			f->b[i.y][i.x] = INT(f->board[i.y][i.x + 4]);
    }
}

/*
** function to convert the **char piece into **int p :
** 1 replaces * and 0 replaces .
*/

void	piece_char2int(t_filler *f)
{
	t_index	i;

	ft_putstr_fd("Piece dim [", 2);
			ft_putnbr_fd(f->piece_dim.y, 2);
			ft_putstr_fd("] [", 2);
			ft_putnbr_fd(f->piece_dim.x, 2);
			ft_putstr_fd("]\n", 2);
	i.y = -1;
    while (++i.y < f->piece_dim.y)
    {
		i.x = -1;
		while (++i.x < f->piece_dim.x)
		{
			f->p[i.y][i.x] = INT2(f->piece[i.y][i.x]);
			ft_putnbr_fd(f->p[i.y][i.x], 2);
		}
		ft_putstr_fd("]\n", 2);
    }
}

void	display_board(t_filler *f)
{
	t_index	i;

	ft_putchar_fd('\n', 2);
	i.y = -1;
    while (++i.y < f->max.y)
    {
		i.x = -1;
		while (++i.x < f->max.x)
		{
			if (!f->b[i.y][i.x])
       			ft_putstr_fd("\033[30m", 2);
			else if (f->b[i.y][i.x] >> 1)
				ft_putstr_fd("\033[31m", 2);
			else
				ft_putstr_fd("\033[32m", 2);
			ft_putnbr_fd(f->b[i.y][i.x], 2);
			ft_putstr_fd("\033[37m", 2);
		}
		ft_putchar_fd('\n', 2);
    }
	ft_putchar_fd('\n', 2);
}

void	display_piece(t_filler *f)
{
	t_index	i;

	ft_putchar_fd('\n', 2);
	i.y = -1;
    while (++i.y < f->piece_dim.y)
    {
		i.x = -1;
		while (++i.x < f->piece_dim.x)
		{
			(!f->p[i.y][i.x]) ? ft_putstr_fd("\033[33m", 2) : ft_putstr_fd("\033[32m", 2);
			ft_putnbr_fd(f->p[i.y][i.x], 2);
			ft_putstr_fd("\033[37m", 2);
      	 	
		}
		ft_putchar_fd('\n', 2);
    }
	ft_putchar_fd('\n', 2);
}

/*
** supress extra rows then extra columns


void	trim_piece_extra_rows(t_filler *f)
{
	t_index	i;
	t_index	del;
	int		tmp;

	i.y = -1;
    while (++i.y < f->piece_dim.y)
    {
		tmp = 0;
		i.x = -1;
		while (++i.x < f->piece_dim.x)
			tmp += f->p[i.y][i.x];
		if (!tmp)
		{
			del.y = i.y - 1;
			while (++del.y < f->piece_dim.y - 1)
    		{
				del.x = -1;
				while (++del.x < f->piece_dim.x)
					f->p[del.y][del.x] = f->p[del.y + 1][del.x];
			}
			--f->piece_dim.y;
		}
    }
}

void	trim_piece_extra_columns(t_filler *f)
{	
	t_index	i;
	t_index	del;
	int		tmp;

	i.x = -1;
    while (++i.x < f->piece_dim.x)
    {
		tmp = 0;
		i.y = -1;
		while (++i.y < f->piece_dim.y)
			tmp += f->p[i.y][i.x];
		if (!tmp)
		{
			del.x = i.x - 1;
			while (++del.x < f->piece_dim.x - 1)
    		{
				del.y = -1;
				while (++i.y < f->piece_dim.y)
					f->p[del.y][del.x] = f->p[del.y][del.x + 1];
			}
			--f->piece_dim.x;
		}
	}
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



/*
** first SKIP_LINE is for skipping 012345...
** then we store into an array data related to the board shape
** second SKIP_LINE is to get piece dimensions (Piece 5 6)
** then we store into an array data related to the piece shape
** third SKIP_LINE is to skip Plateau as we already know board dimensions
*/

void        filler_loop(t_filler *f)
{
    t_index	i;
    char    *line;

    SKIP_LINE;
    i.y = -1;

    while (++i.y < f->max.y)          
        get_next_line(0, &f->board[i.y]);
	
	
    SKIP_LINE;
		
	get_piece(f, line);

//	ft_putchar_fd('\n', 2);
//	ft_putnbr_fd(f->piece_dim.x * f->piece_dim.y, 2);
//	ft_putchar_fd('\n', 2);
	
    i.y = -1;
    while (++i.y < f->piece_dim.y)
        get_next_line(0, &f->piece[i.y]);

	board_char2int(f);
	
	piece_char2int(f);
	ft_putstr_fd("test", 2);
//	trim_piece_extra_rows(f);
//	trim_piece_extra_columns(f);

	
//	display_board(f); // debug
//	display_piece(f); // debug function



//ft_putnbr_fd(f->piece_dim.y, 2);
//ft_putstr_fd("<y x>", 2);
//ft_putnbr_fd(f->piece_dim.x, 2);
//ft_putstr_fd("\n", 2);
	solver(f);
    SKIP_LINE;
	if (i.y != -1)
    	filler_loop(f);
	else
		i.y = -1;
}

/*
** Assuming that VM sends correct data
*/

int		get_board_dimension(t_filler *f, char *s)
{
	t_index	i;

	filler_atoi(&f->max, s + 8);
	if (!(f->board = (char **)malloc(sizeof(char *) * (f->max.y + 1)))
	|| (!(f->b = (int **)malloc(sizeof(int *) * (f->max.y)))))
		EXIT_MSG("Failed to malloc board dimensions");
	i.y = -1;
	while (++i.y < f->max.y)
	{
		if (!(f->board[i.y] = (char *)malloc(6 + f->max.x))
		|| (!(f->b[i.y] = (int *)malloc(f->max.x))))
			EXIT_MSG("Failed to malloc board dimensions");
		f->b[i.y][f->max.x] = '\0';
	}
	return (1);
}

int		get_piece(t_filler *f, char *s)
{
	int i;

	filler_atoi(&f->piece_dim, s + 6);

	if (!(f->piece = (char **)malloc(sizeof(char *) * (f->piece_dim.y + 1)))
	|| (!(f->p = (int **)malloc(sizeof(int *) * (f->piece_dim.y)))))
		EXIT_MSG("Failed to malloc piece");
	i = -1;
	while (++i < f->piece_dim.y)
	{
		if (!(f->piece[i] = (char *)ft_memalloc(f->piece_dim.x + 1))
		|| (!(f->p[i] = (int *)ft_memalloc(f->piece_dim.x + 1))))
			EXIT_MSG("Failed to malloc piece");
		f->piece[i][f->piece_dim.x] = '\0';
	}
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
