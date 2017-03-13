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
		if (b_o(f, b, points->i.y, points->i.x) < b_o(f, b, LAST.y, LAST.x))
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

int		b_o(t_filler *f, BOARD, int y, int x)
{
	t_index	i;
	int		distance;
	int		tmp;

	distance = f->max.y * f->max.y + f->max.x * f->max.x;
	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{
			tmp = (i.y - y) * (i.y - y) + (i.x - x) * (i.x - x);
			if (b[i.y][i.x] >> 1 && next_to_cpu(f, b, i) && tmp < distance)
				if ((distance = tmp) == 2)
					return (distance);
		}
	}
	return (distance);
}