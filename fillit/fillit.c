/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:40:16 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:35:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		fillit(char *av)
{
	char		*input;
	t_map		map;
	t_tetrimino	*ts;
	short		i;

	if (!(input = read_file(av)))
		display_error_message();
	else if (((i = (ft_strlen(input) + 1) / (T_SIZE + 1)) == 0) ||
			((ft_strlen(input) + 1) % (T_SIZE + 1)) != 0)
		display_error_message();
	else if (!(ts = check_validity(input, i)))
		display_error_message();
	else
	{
		ft_strdel(&input);
		map = solve(ts, get_first_size(i), i);
		print_result(get_final_map(&map, ts), &map);
	}
	return (0);
}
