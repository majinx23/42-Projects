/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 16:54:59 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:46:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains printing-related functions.
*/

#include "fillit.h"

/*
** Prints the final result with newlines.
** Frees the map structure, its members and the final map.
*/

void	print_result(char **m, t_map *map)
{
	short	y;

	y = 0;
	while (y < map->size)
	{
		ft_putendl(m[y]);
		free(map->m[y]);
		y++;
	}
	y = 0;
	while (y < map->total - 1)
		free(m[y++]);
	free(m);
	free(map->m);
}
