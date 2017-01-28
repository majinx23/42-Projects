/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/29 00:17:46 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/filler.h"

char	**new_board(int y, int x)
{
	char	**board;
	int		i;

	i = -1;
	board = (char **)malloc(sizeof(char *) * (y + 1));
	while (++i < y)
		board[i] = (char *)malloc(sizeof(char) * (x + 1));
	return (board);
}

char	**new_piece(int y, int x)
{
	char	**piece;
	int		i;

	i = -1;
	piece = (char **)malloc(sizeof(char *) * (y + 1));
	while (++i < y)
		piece[i] = (char *)malloc(sizeof(char) * (x + 1));
	return (piece);

}

int		ft_tab_len(char **tab)
{
	int	len;

	len = 0;
	while (*tab[len])
		++len;
	return (len);
}

int		get_board_dimension(t_filler *filler, char *s)
{
	char **tab;

	tab = ft_strsplit(s, ' ');
	if (ft_tab_len(tab) == 3)
	{
		if (ft_atoi(tab[1]) > 0 && ft_atoi(tab[2]) > 0)
		{
			filler->max.y = ft_atoi(tab[1]);
			filler->max.x = ft_atoi(tab[2]);
			filler->board = new_board(filler->max.y, filler->max.x);
			free(tab);
			return (1);
		}
	}
	free(tab);
	return (0);
}


/*
void		get_piece(t_filler *filler)
{
	;
}*/