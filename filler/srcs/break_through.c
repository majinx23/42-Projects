/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_through.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:56:39 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/18 02:16:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** strategy involved if the opponent has placement superiority
*/

int		is_disadvantaged(t_filler *f, BOARD, t_index *ply_area)
{
	t_index	i;
	t_index cpu_area;

	cpu_area = (t_index) {.x = 0, .y = 0};
	i.y = f->min_area.y - 1;
	while (++i.y <= f->max_area.y)
	{
		i.x = f->min_area.x -1;
		while (++i.x <= f->max_area.x)
		{
			if (b[i.y][i.x] >> 1 && ++f->cpu_score)
			{
				cpu_area.y += i.y;
				cpu_area.x += i.x;
			}
			else if (b[i.y][i.x] && ++f->ply_score)
			{
				ply_area->y += i.y;
				ply_area->x += i.x;
			}
		}
	}
	return (get_relative_position(f, cpu_area, *ply_area));
}

/*
** function get player's position compared to computer
** SE = South East, NW = North West... etc;
*/

int		get_relative_position(t_filler *f, t_index cpu_area, t_index i)
{
	cpu_area.y /= f->cpu_score;
	cpu_area.x /= f->cpu_score;
	i.y = i.y / f->ply_score - cpu_area.y;
	i.x = i.x / f->ply_score - cpu_area.x;
	if (i.y > 0 && i.x)
		POSITION = (i.x > 0) ? SE : SW;
	else if (i.y < 0 && i.x)
		POSITION = (i.x > 0) ? NE : NW;
	else if (!i.x)
		POSITION = (i.y > 0) ? S : N;
	else
		POSITION = (i.x > 0) ? E : W;
	return ((f->min_area.y > f->max_area.y - f->max.y &&
		(POSITION == SW || POSITION == SE || POSITION == S))
		|| ((f->min_area.x > f->max_area.x - f->max.x) &&
		(POSITION == NE || POSITION == E || POSITION == SE))
		|| ((f->min_area.x <= f->max_area.x - f->max.x) &&
		(POSITION == NW || POSITION == W || POSITION == SW))
		|| ((f->min_area.y <= f->max_area.y - f->max.y) &&
		(POSITION == NW || POSITION == NE || POSITION == N)));
}

/*
** check if we are in the central area compared to cpu
*/

int		has_captured_center(t_filler *f, BOARD)
{
	t_index	i;
	int		check;

	i.y = f->min_area.y - 1;
	while (++i.y < f->max_area.y)
	{
		i.x = f->min_area.x - 1;
		check = 0;
		while (++i.x < f->max_area.x)
			check |= b[i.y][i.x];
		if ((check & 1) && (check & 2))
			return (1);
	}
	i.x = f->min_area.x - 1;
	while (++i.x < f->max_area.x)
	{
		i.y = f->min_area.y - 1;
		check = 0;
		while (++i.y < f->max_area.y)
			check |= b[i.y][i.x];
		if ((check & 1) && (check & 2))
			return (1);
	}
	return (0);
}

/*
** we send T or B (TOP or BOTTOM) for char tb and L or R for lr
*/

void		get_direction(t_filler *f, BOARD)
{
	char		lr;
	char		tb;

	lr = (f->position == SE || f->position == NE
		|| f->position == S || f->position == N ? 'L' : 'R');
	tb = (f->position == SE || f->position == SW
		|| f->position == S ? 'T' : 'B');
	ft_putendl_fd("", 2);//
//	ft_putstr_fd(&lr, 2);//
	ft_putendl_fd(&tb, 2);//
	ft_putendl_fd("", 2);//
	f->dir.x = (lr = 'L' ? -1 : 1);
	f->dir.y = (tb = 'T' ? -1 : 1);
	reach_borders(f, b);
}

/*
** try to break through to be fight on equal ground
*/

void	break_through(t_filler *f, BOARD, t_point *points)
{
	get_direction(f, b);
//	ft_putendl_fd("break through !", 2);
	LAST = points->i;
	while (points)
	{
		if (g_d2(f, b, points->i) < g_d2(f, b, LAST))
			LAST = points->i;
/*		if (f->dir.y < 0)
		{
			if ((f->dir.x < 0 && points->i.y > LAST.y && points->i.x < LAST.x)
			||	(f->dir.x > 0 && points->i.y > LAST.y && points->i.x > LAST.x))
					LAST = points->i;
		}
		else
		{
			if ((f->dir.x < 0 && points->i.y < LAST.y && points->i.x < LAST.x)
			||	(f->dir.x > 0 && points->i.y < LAST.y && points->i.x > LAST.x))
					LAST = points->i;
		}*/

		points = points->next;
	}
}



int		g_d2(t_filler *f, BOARD, t_index p)
{
	t_index	i;
	int		distance;
	int		tmp;

	distance = f->max.y * f->max.y + f->max.x * f->max.x;
	if ((f->goal & 1) || (f->goal & 8))
	{
		i.y = ((f->goal & 1) ? 0 : f->max.y - 1);
		distance = (i.y - p.y) * (i.y - p.y);
	}
	else if ((f->goal & 2) || (f->goal & 4))
	{
		i.x = ((f->goal & 2) ? 0 : f->max.x - 1);
		distance = (i.x - p.x) * (i.x - p.x);
	}
	return (distance);

	/*
	while (++i.y < f->max.y)
	{
		tmp = (i.y - p.y) * (i.y - p.y) + (i.x - p.x) * (i.x - p.x);




		i.x = -1;
		while (++i.x < f->max.x)
		{
			tmp = (i.y - p.y) * (i.y - p.y) + (i.x - p.x) * (i.x - p.x);
			if (b[i.y][i.x] >> 1 && tmp < distance)
				if ((distance = tmp) == 2)
					return (distance);
		}
	}
	return (distance);*/
}

/*
** function check which would be the best direction


int		get_direction(t_filler *f, BOARD, t_index i)
{
	t_index	i;
	
	if (POSITION == SE)
	{
		if ()

	}
	return (0);
}
*/
/*
** scoring system : keep only the best point


int		score(t_filler *f, BOARD, t_index p)
{
	t_index	i;
	int		score;

	score = 0;
	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{
	//		score += get_board_limit(f, b, i, p);
	//		score += get_board_size();
	//		score += ();

		}
	}
	return (score);
}*/

/*
** absolute priority if piece is close to the cpu
*/

int		get_board_limit(t_filler *f, BOARD, t_index i)
{
	return ((i.y >= 0 && i.y < f->max.y
		&& (b[i.y + 1][i.x] >> 1 || b[i.y - 1][i.x] >> 1))
	|| (i.x > 0 && i.x < f->max.x - 1
		&& (b[i.y][i.x + 1] >> 1 || b[i.y][i.x - 1] >> 1))
	|| (!i.y && b[i.y + 1][i.x] >> 1) || (!i.x && b[i.y][i.x + 1] >> 1)
	|| (i.y == f->max.y - 1 && b[i.y - 1][i.x] >> 1)
	|| (i.x == f->max.x - 1 && b[i.y][i.x - 1] >> 1));
}

/*
** function to check trimmed board limits (min point and max point)
*/

void	check_min_ply(t_filler *f, BOARD)
{
	t_index	i;

	f->min_ply.y = -1;
	i.y = f->min_area.y - 1;
	while (++i.y < f->max_area.y)
	{
		i.x = f->min_area.y - 1;
		while (++i.x < f->max_area.x)
			if (b[i.y][i.x] & 1 && f->min_ply.y == -1)
				f->min_ply.y = i.y;
			else if (b[i.y][i.x] >> 1 && f->min_cpu.y == -1)
				f->min_ply.y = i.y;
	}
	f->min_ply.x = -1;
	i.x = f->min_area.x -1;
	while (++i.x < f->max_area.x && f->min_ply.x == -1 && f->min_cpu.y == -1)
	{
		i.y = -1;
		while (++i.y < f->max_area.y && f->min_ply.x == -1)
			if (b[i.y][i.x] == 1)
				f->min_area.x = i.x;
	}
}

void	check_max_ply(t_filler *f, BOARD)
{
	t_index	i;

	i.y = f->max_area.y;
	f->max_ply.y = -1;
	while (--i.y >= 0 && f->max_ply.y == -1)
	{
		i.x = f->max_area.x;
		while (--i.x >= 0 && f->max_ply.y == -1)
		{
			if (b[i.y][i.x] == 1)
				f->max_ply.y = i.y;
		}
	}
	f->max_ply.x = -1;
	i.x = f->max_area.x;
	while (--i.x >= 0 && f->max_ply.x == -1)
	{
		i.y = f->max_area.y;
		while (--i.y >= 0 && f->max_ply.x == -1)
		{
			if (b[i.y][i.x] == 1)
				f->max_ply.x = i.x;
		}
	}
}