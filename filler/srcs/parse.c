/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 16:48:10 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

int		filler_atoi(char *s)
{
	int		sign;
	int		r;

	r = 0;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	sign = (*s == '-') ? -1 : 1;
	(*s == '-' || *s == '+') ? s++ : s;
	while (*s >= '0' && *s <= '9')
	{
		r = r * 10 + *s++ - '0';
	}
	return (sign * r);
}

/*
** Assuming that VM sends correct data
*/

int		get_board_dimension(t_filler *f, char *s)
{
	int 	i;

	f->max.y = filler_atoi(s);
	f->max.x = filler_atoi(s);
	if (f->max.y > 0 && f->max.x > 0)
	{
		f->board = (char **)malloc(sizeof(char *) * (f->max.y + 1));
		i = -1;
		while (++i < f->max.y)
			f->board[i] = (char *)ft_memalloc(f->max.x + 1);
	}
	return (1);
}

int		get_piece(t_filler *filler, char *s)
{
	int i;

    filler->piece_dim.y = filler_atoi(s);
	filler->piece_dim.x = filler_atoi(s);
	if (filler->piece_dim.y > 0 && filler->piece_dim.x > 0)
	{	
		filler->piece = (char **)malloc(sizeof(char *) * (filler->piece_dim.y + 1));
		i = -1;
		while (++i < filler->piece_dim.y)
			filler->piece[i] = (char *)ft_memalloc(filler->piece_dim.x + 1);
	}
	return (1);
}