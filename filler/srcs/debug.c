/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:47:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/18 18:48:30 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	display_min(t_filler *f)
{
	ft_putstr_fd("min dim (y, x) : (", 2);
	ft_putnbr_fd(f->min_dim.y, 2);
	ft_putstr_fd(", ", 2);
	ft_putnbr_fd(f->min_dim.x, 2);
	ft_putstr_fd(")\n", 2);
}

void	display_last(t_filler *f)
{
	ft_putstr_fd("LAST (y, x) : (", 2);
	ft_putnbr_fd(LAST.y - f->min_dim.y, 2);
	ft_putstr_fd(", ", 2);
	ft_putnbr_fd(LAST.x - f->min_dim.x, 2);
	ft_putstr_fd(")\n", 2);
}

void	feed_board(t_index max, int b[max.y][max.x])
{
	t_index	i;
	int		fd;
	
	system("touch board.map");
	fd = open("board.map", O_WRONLY | O_APPEND);
	i.y = -1;
    while (++i.y < max.y)
    {
		i.x = -1;
		while (++i.x < max.x)
			ft_putnbr_fd(b[i.y][i.x], fd);
		ft_putchar_fd('\n', fd);
    }
	ft_putchar_fd('\n', fd);
}

void	display_board(t_index max, int b[max.y][max.x])
{
	t_index	i;

	ft_putchar_fd('\n', 2);
	i.y = -1;
    while (++i.y < max.y)
    {
		i.x = -1;
		while (++i.x < max.x)
		{
			if (!b[i.y][i.x])
       			ft_putstr_fd("\033[30m", 2);
			else if (b[i.y][i.x] >> 1)
				ft_putstr_fd("\033[31m", 2);
			else
				ft_putstr_fd("\033[32m", 2);
			ft_putnbr_fd(b[i.y][i.x], 2);
			ft_putstr_fd("\033[37m", 2);
		}
		ft_putchar_fd('\n', 2);
    }
	ft_putchar_fd('\n', 2);
}

void	display_miniboard(t_filler *f, t_index min, t_index max, int b[f->max.y][f->max.x])
{
	t_index	i;

	ft_putchar_fd('\n', 2);
	i.y = min.y -1;
    while (++i.y <= max.y)
    {
		i.x = min.x -1;
		while (++i.x <= max.x)
		{
			if (!b[i.y][i.x])
       			ft_putstr_fd("\033[30m", 2);
			else if (b[i.y][i.x] >> 1)
				ft_putstr_fd("\033[31m", 2);
			else
				ft_putstr_fd("\033[32m", 2);
			ft_putnbr_fd(b[i.y][i.x], 2);
			ft_putstr_fd("\033[37m", 2);
		}
		ft_putchar_fd('\n', 2);
    }
	ft_putchar_fd('\n', 2);
}

void	display_piece(t_index max, int p[max.y][max.x])
{
	t_index	i;

	ft_putchar_fd('\n', 2);
	i.y = -1;
    while (++i.y < max.y)
    {
		i.x = -1;
		while (++i.x < max.x)
		{
			(!p[i.y][i.x]) ? ft_putstr_fd("\033[33m", 2) : ft_putstr_fd("\033[32m", 2);
			ft_putnbr_fd(p[i.y][i.x], 2);
			ft_putstr_fd("\033[37m", 2);
      	 	
		}
		ft_putchar_fd('\n', 2);
    }
	ft_putchar_fd('\n', 2);
}


void	display_turn_nb(t_filler *f)
{
	ft_putstr_fd("\033[32m", 2);
	ft_putstr_fd("~~~ Turn ", 2);
	ft_putnbr_fd(f->turn, 2);
	ft_putstr_fd(" ~~~\nPLY: ", 2);
	ft_putnbr_fd(f->ply_score, 2);
	ft_putstr_fd(" vs CPU: ", 2);
	ft_putnbr_fd(f->cpu_score, 2);
	ft_putstr_fd("\n", 2);
	f->ply_score = 0;
	ft_putstr_fd("\033[37m", 2);
	++f->turn;
}

/*
** function to free our list once our piece is returned
*/

void	display_points(t_point **points)
{
	t_point	*lst;

	lst = *points;
	while (lst)
	{
		ft_putstr_fd("(", 2);
		ft_putnbr_fd(lst->i.y, 2);
		ft_putstr_fd(", ", 2);
		ft_putnbr_fd(lst->i.x, 2);
		ft_putstr_fd(")\n", 2);
		lst = lst->next;
	}
}
