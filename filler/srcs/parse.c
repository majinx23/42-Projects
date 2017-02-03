/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/03 15:26:45 by angavrel         ###   ########.fr       */
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
	char **tab;

	tab = ft_strsplit(s, ' ');
	if (ft_atoi(tab[1]) > 0 && ft_atoi(tab[2]) > 0)
	{
		filler->max.y = ft_atoi(tab[1]);
		filler->max.x = ft_atoi(tab[2]);
		filler->board = (char **)malloc(sizeof(char *) * (filler->max.y + 1));
		return (1);
	}
	free(tab);
	return (0);
}

int		get_piece(t_filler *filler, char *s)
{
	char **tab;

	tab = ft_strsplit(s, ' ');
	if (ft_atoi(tab[1]) > 0 && ft_atoi(tab[2]) > 0)
	{
		filler->piece_dim.y = ft_atoi(tab[1]);
		filler->piece_dim.x = ft_atoi(tab[2]);
		filler->piece = (char **)malloc(sizeof(char *) * (filler->piece_dim.y + 1));
		return (1);
	}
	free(tab);
	return (0);
}