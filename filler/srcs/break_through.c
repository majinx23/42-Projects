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
	(get_relative_position(f, cpu_area, *ply_area) ?
		ft_putnbr_fd(1, 2) : ft_putnbr_fd(0, 2));
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
** try to break through to be fight on equal ground
*/

void	break_through(t_filler *f, BOARD, t_point *points)
{
//	get_direction(f, b);
	LAST = points->i;
	while (points)
	{
		if (score(f, b, points->i) > score(f, b, LAST))
			LAST = points->i;
		points = points->next;
	}
}

/*
** function check which would be the best direction
*/
/*
int		get_direction(t_filler *f, BOARD)
{
	t_index	i;
	
	i.y = f->min_area.y - 1;
	while (++i.y <= f->max_area.y)
	{
		i.x = f->min_area.x -1;
		while (++i.x <= f->max_area.x)
		{
			if (b[i.y][i.x] >> 1)

		}
	}
	return (0);
}*/

/*
** best_odds : keep only the best point
*/

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
}

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