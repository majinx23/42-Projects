/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 23:57:05 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdio.h> //printf to be removed before final push
# include "libft.h"

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

typedef struct	s_filler
{
	char	**board;
	char	**piece;
	t_index	max;
	int		player;
}				t_filler;

int		get_board_dimension(t_filler *filler, char *s);
int		et_player_position(char *s);

char	**new_board(int y, int x);
char	**new_piece(int y, int x);

#endif
