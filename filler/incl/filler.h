/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/11 06:16:38 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include <mlx.h>

/*
** mathematics functions used as define
*/

# define MAX(a, b)			(a > b ? a : b)
# define MIN(a, b)			(a < b ? a : b)

/*
** Board and Piece are saved on the stack
** INT converts board dta into 2 (opponent), 1 (player) and 0 (.)
** INT2 convert piece data into 1 (*) amd 0 (.) 
*/

# define BOARD			int b[f->max.y][f->max.x]
# define PIECE			int p[f->piece_dim.y][f->piece_dim.x]
# define INT2(c)		(int)((46 - c) >> 2)

/*
** other usefull define
** SKIP_LINE to skip useless lines
** LAST it the last point sent to the Virtual Machine
** Exit messg is to exit;
*/

# define SKIP_LINE		get_next_line(0, &line)
# define PLY			f->player
# define LAST 			f->last_p

/*
** structure for (y, x) points
*/

typedef struct	s_index
{
	int			x;
	int			y;
}				t_index;
			
/*
** this list saved all valid positions
*/

typedef struct		s_point
{
	t_index			i;
	struct s_point	*next;
}					t_point;

/*
** structure for graphic bonus
*/

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
** max is max dimension y and x of the board
** player is the position of the player.
*/

typedef struct	s_filler
{
	int			cpu;
	int			player;
	t_index		max;
	t_index		piece_dim;
	t_index		min_dim;
	t_index		last_p;
	int			turn;
	t_env		*env;
}				t_filler;

/*
** debug/display functions ~ debug.c//
*/

void			display_min(t_filler *f);//
void			display_board(t_index max, int b[max.y][max.x]);//
void			display_piece(t_index max, int p[max.y][max.x]);//
void			display_last(t_filler *f);//
void			display_turn_nb(t_filler *f);//
void			display_points(t_point **points);//

/*
** initialization and parsing functions ~ parse.c
*/

void			filler_loop(t_filler *filler);
void			board_char2int(t_filler *f, char *s, int y, BOARD);
void			filler_atoi(t_index *i, char *s);
void 			free_piece(t_filler *f, PIECE);
void			get_piece_dimension(t_filler *f, char *line, BOARD);
void			trim_piece(t_filler *f, PIECE);
int				check_min(t_filler *f, int y, int x, PIECE);

/*
** solving algos ~ solver.c
*/

void			solver(t_filler *f, BOARD, PIECE);
void			return_piece(int a, int b);
void			surround(t_filler *f, BOARD, t_point *points);
int				g_d(t_filler *f, BOARD, int y, int x);
int				next_to_cpu(t_filler *f, BOARD, t_index i);

/*
** Save relevant (y, x) valid positions inside a list ~ valid_positions.c
*/

int				put_piece(t_filler *f, BOARD, PIECE, t_point **points);
int				is_valid_position(t_filler *f, BOARD, PIECE, t_index c);
void			add_point(t_point **points, int y, int x);
t_point			*new_point(int y, int x);
void			free_saved_positions(t_point **points);

/*
** mlx interaction... to be done later
*/

void			update_board(t_filler *f, BOARD);
void			ft_init_win(t_env *env, t_index max);

#endif
