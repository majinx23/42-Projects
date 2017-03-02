/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/02 14:51:56 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdio.h> //printf to be removed before final push
# include "libft.h"
# include <mlx.h>

# define SKIP_LINE		get_next_line(0, &line)
# define PLY			f->player
# define CPU			f->cpu
# define LAST 			f->last_p
# define EXIT_MSG(s)	ft_putstr("\033[31m"), ft_putendl(s), exit(-1)
# define C				f->cpu_closest_piece
# define J				f->player_closest_piece
# define INT(c)			(int)((c - 46) / 21)
# define INT2(c)		(int)((46 - c) >> 2)
# define BOARD			char b[f->max.y][f->max.x]
# define PIECE			char p[f->piece_dim.y][f->piece_dim.x]

typedef struct	s_index
{
	int			x;
	int			y;
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

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			endian;
	int			sl;
	t_index		i;
}				t_env;


/*
** board is the board stocked as char* while b is the board as int *
*/

typedef struct	s_filler
{
	int			cpu;
	int			player;
	t_index		max;
	t_index		piece_dim;
	
	t_index		cpu_closest_piece;
	t_index		player_closest_piece;
	int			distance;

	t_index		padding;
	t_index		last_p;
	int			found;

	int			score;
	t_corners	corners;
	int			turn;
	t_env		*env;
}				t_filler;


/*
** initialization and parsing functions
*/

void			init_filler(t_filler *f);
int				get_board_dimension(t_filler *filler, char *s);

void			filler_loop(t_filler *filler);
void			filler_atoi(t_index *i, char *s);
void			get_piece(t_filler *f, char *line, char b[f->max.y][f->max.x]);
void			board_char2int(t_index max, char b[max.y][max.x]);
void			piece_char2int(t_index max, char p[max.y][max.x]);

/*
** debug/display functions//
*/
void			display_board(t_index max, char b[max.y][max.x]);//
void			display_piece(t_index max, char p[max.y][max.x]);//

/*
** solving algos
*/

void			solver(t_filler *f, BOARD, PIECE);
void			shortest_distance(t_filler *f, BOARD, PIECE);
int				player_closest(t_filler *f, BOARD, PIECE);
int				put_piece_on_J(t_filler *f, BOARD, PIECE);
int				piece_valid_position(t_filler *f, BOARD, PIECE);
int				put_piece(t_filler *f, BOARD, PIECE);

void			return_piece(int a, int b);

/*
** filler interaction
*/

void			update_board(t_filler *f, BOARD);
void			ft_init_win(t_env *env, t_index max);
#endif
