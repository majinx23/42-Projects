/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:49:43 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/18 19:54:21 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** functions to check x and y minimum and maximum point
** for both computer (b[i.y][i.x] >> 1) and player (b[i.y][i.x] & 1)
*/

void	check_min(t_filler *f, BOARD)
{
	t_index	i;

    f->min_ply = (t_index) {.x = -1, .y = -1};
    f->min_cpu = (t_index) {.x = -1, .y = -1};
	i.y = f->min_area.y - 1;
	while (++i.y < f->max_area.y && f->min_ply.y < 0 && f->min_cpu.y < 0)
	{
		i.x = f->min_area.y - 1;
		while (++i.x < f->max_area.x)
            if ((b[i.y][i.x] & 1) && f->min_ply.y == -1)
				f->min_ply.y = i.y;
			else if (b[i.y][i.x] >> 1 && f->min_cpu.y == -1)
				f->min_cpu.y = i.y;
	}
	i.x = f->min_area.x - 1;
	while (++i.x < f->max_area.x && f->min_ply.x < 0 && f->min_cpu.x < 0)
	{
		i.y = f->min_area.y - 1;
		while (++i.y < f->max_area.y && f->min_ply.x == -1)
            if ((b[i.y][i.x] & 1) && f->min_ply.x == -1)
				f->min_ply.x = i.x;
            else if (b[i.y][i.x] >> 1 && f->min_cpu.x == -1)
				f->min_cpu.x = i.x;
	}
}

void	check_max(t_filler *f, BOARD)
{
	t_index	i;

    f->max_ply = (t_index) {.x = -1, .y = -1};
    f->max_cpu = (t_index) {.x = -1, .y = -1};
	i.y = f->max_area.y;
	while (--i.y >= f->min_area.y && f->max_ply.x < 0 && f->max_cpu.x < 0)
	{
		i.x = f->max_area.y;
		while (++i.x < f->max_area.x)
            if ((b[i.y][i.x] & 1) && f->max_ply.y == -1)
				f->max_ply.y = i.y;
			else if (b[i.y][i.x] >> 1 && f->max_cpu.y == -1)
				f->max_cpu.y = i.y;
	}
	i.x = f->max_area.x;
	while (--i.x >= f->min_area.x && f->min_ply.x == -1 && f->min_cpu.y < 0)
	{
		i.y = f->max_area.y;
        while (--i.y >= f->min_area.y)
            if ((b[i.y][i.x] & 1) && f->max_cpu.x == -1)
				f->max_ply.x = i.x;
            else if (b[i.y][i.x] >> 1 && f->max_cpu.x == -1)
				f->max_cpu.x = i.x;
	}
}
