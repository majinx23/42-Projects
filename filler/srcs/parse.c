/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/02 18:05:21 by angavrel         ###   ########.fr       */
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
	t_filler	f;
	t_env		env;
    char        *line;

	ft_bzero(&env, sizeof(t_env));
	f.env = &env;
	init_filler(&f);
    get_next_line(0, &line);//$$$ exec p[1-2]
	f.player = (line[10] - '1') ? 2 : 1;
	f.cpu = (f.player >> 1) ? 1 : 2;
    get_next_line(0, &line);//Plateau 14 17:       
  	filler_atoi(&f.max, line + 8);
//	ft_init_win(f.env, f.max);
    filler_loop(&f);
	return (0);
}

/*
** variables initialization
*/

void		init_filler(t_filler *f)
{
    LAST = (t_index) {.y = 8, .x = 2};
	f->cpu_closest_piece = (t_index) {.y = 0, .x = 0};
	f->distance = 2147483647;
	f->turn = 0;
	f->piece_dim = (t_index) {.y = 8, .x = 0};
	f->max = (t_index) {.y = 8, .x = 0};
}

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
	char	b[f->max.y][f->max.x];

    SKIP_LINE;
    i.y = -1;
    while (++i.y < f->max.y)
	{
        get_next_line(0, &line);
		ft_strcpy(b[i.y], line + 4);
	}
//		ft_putnbr_fd(f.max.x, 2);
	board_char2int(f->max, b);
    SKIP_LINE;
	filler_atoi(&f->piece_dim, line + 6);
	trim_piece(f, line, b);
    SKIP_LINE;
	if (i.y != -1)
    	filler_loop(f);
	else
		i.y = -1;
}

/*
void	get_piece(t_filler *f, char *line, char b[f->max.y][f->max.x])
{
	t_index	i;
	char	p[f->piece_dim.y][f->piece_dim.x];

	i.y = -1;
    while (++i.y < f->piece_dim.y)
	{
		 get_next_line(0, &line);
		 ft_strcpy(p[i.y], line);
	}
	piece_char2int(f->piece_dim, p);
	display_board(f->max, b); // debug
	display_piece(f->piece_dim, p); // debug function
	solver(f, b, p);
}
*/

/*
** remove extra rows and columns from transmitted piece
*/

void	trim_piece(t_filler *f, char *line, BOARD)
{
	char	tmp[f->piece_dim.y][f->piece_dim.x];
	t_index	i;
	t_index	t;

	i.y = -1;
    while (++i.y < f->piece_dim.y)
	{
		 get_next_line(0, &line);
		 ft_strcpy(tmp[i.y], line);
	}
	piece_char2int(f, f->piece_dim, tmp);
	t = f->piece_dim;
	f->piece_dim.y = f->max_dim.y - f->min_dim.y + 1;
	f->piece_dim.x = f->max_dim.x - f->min_dim.x + 1;
						
	ft_putendl_fd(" min dim.x\n", 2);
	ft_putnbr_fd(f->piece_dim.x, 2);
/*	ft_putnbr_fd(f->min_dim.x, 2);
ft_putendl_fd(" min dim.x\n", 2);
	ft_putnbr_fd(f->min_dim.y, 2);
	ft_putendl_fd(" min dim.x\n", 2);
	ft_putnbr_fd(f->max_dim.x, 2);
	ft_putendl_fd(" max dim.x\n", 2);
	ft_putnbr_fd(f->max_dim.y, 2);
	ft_putendl_fd(" max dim.y\n", 2);*/
	get_piece(f, b, t, tmp);
}

/*
**
*/

void	get_piece(t_filler *f, BOARD, t_index t, char tmp[t.y][t.x])
{
	char	p[f->piece_dim.y][f->piece_dim.x];
	t_index	i;
	t_index	new;

	i.y = f->min_dim.y -1;
	new.y = 0;
    while (++i.y <= f->max_dim.y)
	{
		new.x = 0;
		i.x = f->min_dim.x -1;
		while (++i.x <= f->max_dim.x)
		{
			p[new.y][new.x] = tmp[i.y][i.x];
			++new.x;
		}
		++new.y;
	}
	display_board(f->max, b); // debug
	display_piece(f->piece_dim, p); // debug function
	solver(f, b, p);
}

/*
** reset y and x value then
** getting y, skipping the space, getting x.
*/

void	filler_atoi(t_index *max, char *s)
{
	int		r;

	r = 0;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + *s++ - '0';
	max->y = r;
	++s;
	r = 0;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + *s++ - '0';
	max->x = r;
	if (max->x <= 0 || max->y <= 0)
		EXIT_MSG("Wrong dimensions");	
}

/*
** function to convert the board into ints :
** 1 for Player and 2 for CPU, 0 if empty.
*/

void	board_char2int(t_index max, char b[max.y][max.x])
{
	t_index	i;

	i.y = -1;
    while (++i.y < max.y)
    {
		i.x = -1;
		while (++i.x < max.x)
			b[i.y][i.x] = INT(b[i.y][i.x]);
    }
}

/*
** function to convert the **char piece into **int p :
** 1 replaces * and 0 replaces .
*/

void	piece_char2int(t_filler *f, t_index max, char p[max.y][max.x])
{
	t_index	i;

	f->min_dim = (t_index) {.y = max.y, .x = max.x};
//	f->min_dim.y = max.y;
//	f->min_dim.x = max.x;
	f->max_dim = (t_index) {.y = 0, .x = 0};

	i.y = -1;
    while (++i.y < max.y)
    {
		i.x = -1;
		while (++i.x < max.x)
		{
			p[i.y][i.x] = INT2(p[i.y][i.x]);
			if (p[i.y][i.x])
			{
				f->max_dim.y = MAX(f->max_dim.y, i.y);
				f->max_dim.x = MAX(f->max_dim.x, i.x);
	//			if (i.y < f->min_dim.y)
	//				f->min_dim.y = i.y;
	//			if (i.x< f->min_dim.x)
	//				f->min_dim.x = i.x;	
				f->min_dim.y = MIN(f->min_dim.y, i.y);
				f->min_dim.x = MIN(f->min_dim.x, i.x);
	//			ft_putnbr_fd(f->min_dim.x, 2);
	//			ft_putendl_fd("hahgagagaegegaeg\n", 2);

			}
		}
    }
	
}

void	display_board(t_index max, char b[max.y][max.x])
{
	t_index	i;

	ft_putchar_fd('\n', 2);
	i.y = -1;
    while (++i.y < max.y)
    {
		i.x = -1;
		while (++i.x < max.x)
		{
			if (!b[i.y][i.x])
       			ft_putstr_fd("\033[30m", 2);
			else if (b[i.y][i.x] >> 1)
				ft_putstr_fd("\033[31m", 2);
			else
				ft_putstr_fd("\033[32m", 2);
			ft_putnbr_fd(b[i.y][i.x], 2);
			ft_putstr_fd("\033[37m", 2);
		}
		ft_putchar_fd('\n', 2);
    }
	ft_putchar_fd('\n', 2);
}

void	display_piece(t_index max, char p[max.y][max.x])
{
	t_index	i;

	ft_putchar_fd('\n', 2);
	i.y = -1;
    while (++i.y < max.y)
    {
		i.x = -1;
		while (++i.x < max.x)
		{
			(!p[i.y][i.x]) ? ft_putstr_fd("\033[33m", 2) : ft_putstr_fd("\033[32m", 2);
			ft_putnbr_fd(p[i.y][i.x], 2);
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



