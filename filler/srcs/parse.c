/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 17:14:55 by angavrel         ###   ########.fr       */
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

    SKIP_LINE;//launched ...
    get_next_line(0, &line);//$$$ exec p[1-2]
    f->player = (line[10] - '1') ? 'x' : 'o';
    f->cpu = (f->player == 'x') ? 'o' : 'x';
    get_next_line(0, &line);//Plateau 14 17:      
    if (!get_board_dimension(f, line))
        ft_error("Wrong board dimensions");
    filler_loop(f);
    return ;
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
		if (!(f->board = (char **)malloc(sizeof(char *) * (f->max.y + 1))))
			return (0);
		i = -1;
		while (++i < f->max.y)
			if (!(f->board[i] = (char *)malloc(f->max.x + 1)))
				return (0);
	}
	return (1);
}

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