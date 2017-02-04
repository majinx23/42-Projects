/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:18:24 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 16:10:27 by angavrel         ###   ########.fr       */
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


void	play_piece(int a, int b)
{
	char	*s;
	t_index	tmp;
	t_index	i;

	tmp.x = a;
	tmp.y = b;
	i.x = (a < 0) ? 2 : 1;
	i.y = (b < 0) ? 2 : 1;
	while ((tmp.x /= 10) >= 1)
		++i.x;
	while ((tmp.y /= 10) >= 1)
		++i.y;
	if (!(s = (char*)malloc(sizeof(char) * (i.x + i.y + 3))))
		return ;	
	s[i.x] = ' ';
	s[i.x + i.y + 1] = '\n';
	s[i.x + i.y + 2] = '\0';
	while (i.y-- && (s[i.x + 1 + i.y] = b % 10 + '0'))
		b /= 10;
	while (i.x-- && (s[i.x] = a  % 10 + '0'))
		a /= 10;
	ft_putstr(s);
	free(s);
}


/*
** Assuming that VM sends correct data
*/

int		get_board_dimension(t_filler *f, char *s)
{
	int 	i;

	f->max.y  = filler_atoi(s);
	f->max.x = filler_atoi(s);
	play_piece(8, 2);
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