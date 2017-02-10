/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/10 21:48:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdio.h> //printf to be removed before final push
# include "libft.h"

# define SKIP_LINE		get_next_line(0, &line)
# define PLY			f->player
# define CPU			f->cpu
# define LAST 			f->last_p
# define EXIT_MSG(s)	ft_putstr("\033[31m"), ft_putendl(s), exit(-1)
# define C				f->cpu_closest_piece
# define J				f->player_closest_piece
# define INT(c)			(int)((c - 46) / 21)
# define INT2(c)		(int)((46 - c) >> 2)

typedef struct	s_index
{
	int	x;
	int	y;
}				t_index;

/*
** board is the board
** max is max dimension y and x of the board
** player is the position of the player.
*/

typedef struct	s_corners
{
	t_index		nw;
	t_index		sw;
	t_index		ne;
	t_index		se;
}				t_corners;




/*
** board is the board stocked as char* while b is the board as int *
*/

typedef struct	s_filler
{
	int			cpu;
	int			player;

	char		**b;
	t_index		max;
	
	char		**p;
	t_index		piece_dim;
	
	t_index		cpu_closest_piece;
	t_index		player_closest_piece;
	int			distance;

	t_index		padding;
	t_index		last_p;
	int			found;


	t_corners	corners;
	int			turn;
}				t_filler;


/*
** initialization and parsing functions
*/

t_filler		*init_filler(void);
int				get_board_dimension(t_filler *filler, char *s);
void			filler_atoi(t_index *i, char *s);
int				get_piece(t_filler *filler, char *s);
void			board_char2int(t_filler *f);
void			piece_char2int(t_filler *f);

/*
** solving algos
*/

void			filler_loop(t_filler *filler);
void			solver(t_filler *filler);
int				put_piece(t_filler *filler);
void			return_piece(int a, int b);
void			shortest_distance(t_filler *f);
int				player_closest(t_filler *f);
int				try_put_piece_around_J(t_filler *f);
int				try_put_piece(t_filler *f);

#endif
