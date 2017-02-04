/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/03 19:56:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

//char	**new_board(int y, int x)
//{
//	char	**board;
//	int		i;

//	i = -1;
//	board = (char **)malloc(sizeof(char *) * (y + 1));
	//while (++i < y)// malloc by GNL
//		board[i] = (char *)malloc(sizeof(char) * (x + 1));
//	return (board);
//}
int		ft_tab_len(char **tab)
{
	int	len;

	len = 0;
	while (*tab[len])
		++len;
	return (len);
}

/*
** Assuming that VM sends correct data
*/

int		get_board_dimension(t_filler *filler, char *s)
{
	int 	i;
	char	**tab;

	tab = ft_strsplit(s, ' ');
	filler->max.y  = ft_atoi(tab[1]);
	filler->max.x = ft_atoi(tab[2]);
    free(tab);
	if (filler->max.y > 0 && filler->max.x > 0)
	{
		filler->board = (char **)malloc(sizeof(char *) * (filler->max.y + 1));
		i = -1;
		while (++i < filler->max.y)
			filler->board[i] = (char *)ft_memalloc(filler->max.x + 1);
	}
	return (1);
}

int		get_piece(t_filler *filler, char *s)
{
	int i;
	char **tab;

	tab = ft_strsplit(s, ' ');
    filler->piece_dim.y = ft_atoi(tab[1]);
	filler->piece_dim.x = ft_atoi(tab[2]);
    free(tab);
	if (filler->piece_dim.y > 0 && filler->piece_dim.x > 0)
	{	
		filler->piece = (char **)malloc(sizeof(char *) * (filler->piece_dim.y + 1));
		i = -1;
		while (++i < filler->piece_dim.y)
			filler->piece[i] = (char *)ft_memalloc(filler->piece_dim.x + 1);
	}
	return (1);
}