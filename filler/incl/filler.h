/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 16:21:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdio.h> //printf to be removed before final push
# include "libft.h"

# define SKIP_LINE	get_next_line(0, &line)
# define P			f->player
# define C			f->cpu
# define LAST 		f->last_p
# define CURRENT	f->piece_dim

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

typedef struct	s_filler
{
	char		**board;
	t_index		max;
	
	char		**piece;
	t_index		piece_dim;
	t_index		last_p;
	
	char		cpu;
	char		player;

	t_corners	corners;
}				t_filler;

/*
** parsing functions
*/

void			parsing(t_filler *filler);
t_filler		*init_filler(void);
int				ft_tab_len(char **tab);
int				get_board_dimension(t_filler *filler, char *s);
int				get_piece(t_filler *filler, char *s);
void			filler_loop(t_filler *filler);

/*
** solving algos
*/

void			solver(t_filler *filler);
int				put_piece(t_filler *filler);
void			return_piece(int a, int b);

#endif
