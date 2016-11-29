/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:23:51 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 16:42:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Takes a string containing the contents of the file.
** Calls on other functions to check the validity of the input.
** Returns an array of validated t_tetrimino structs.
*/

t_tetrimino	*check_validity(char *input, short num)
{
	char	**ts;

	if (check_input_length(input, num) == 0)
		return (NULL);
	ts = t_split(input, num);
	if (!check_t_format(ts) || !check_full_char(ts))
		return (NULL);
	return (set_tetriminos(ts, num));
}

/*
** Checks if the number of tetriminos if valid.
** Checks if the length of the entire file is valid.
** Checks the location of newlines.
*/

short		check_input_length(char *t, short num)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (num > T_MAX)
		return (0);
	while (t[i])
	{
		if (t[i] == '\n')
		{
			count++;
			if (count == 5)
			{
				if (t[i - 1] != '\n')
					return (0);
				count = 0;
			}
		}
		i++;
	}
	return ((ft_strlen(t) + 1) % (T_SIZE + 1) == 0);
}

/*
** Checks the location of newlines in each tetrimino.
*/

short		check_t_format(char **ts)
{
	short	i;
	short	j;

	i = 0;
	while (ts[i])
	{
		j = 0;
		while (ts[i][j])
		{
			if ((j + 1) % T_WIDTH == 0 && ts[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*
** Takes an array of tetriminos and checks if eachpattern is valid. Conditions:
** -each CHAR_FULL char must be next to at least ONE other CHAR_FULL char.
** -there must be at least ONE CHAR_FULL char connected with TWO CHAR_FULL
**  chars (see connections variable).
** Returns 1 if conditions are met, else returns 0.
*/

short		check_full_char(char **ts)
{
	short	i;
	short	j;
	short	n;
	short	connections;

	i = -1;
	while (ts[++i])
	{
		n = 0;
		j = 0;
		connections = 0;
		while (ts[i][j])
		{
			if (ts[i][j] == CHAR_FULL)
				n += check_pattern(ts[i], j, &connections);
			if ((n == 4 && !connections) || (ts[i][j] != CHAR_FULL
						&& ts[i][j] != CHAR_EMPTY && ts[i][j] != '\n'))
				return (0);
			++j;
		}
		if (n != 4 || !connections)
			return (0);
	}
	return (1);
}

/*
** From the char at index i in the tetrimino t, checks if the four spaces
** around it, if they exist, are also CHAR_FULL chars.
** Returns 1 if at least one connection is found.
** If there are more than one connections, connections is set to 1.
*/

short		check_pattern(char *t, short i, short *connections)
{
	short	connected;

	connected = 0;
	if (i - T_WIDTH >= 0 && t[i - T_WIDTH] == CHAR_FULL)
		connected += 1;
	if (i + T_WIDTH < T_SIZE && t[i + T_WIDTH] == CHAR_FULL)
		connected += 1;
	if (i - 1 > 0 && t[i - 1] == CHAR_FULL)
		connected += 1;
	if (i + 1 < T_SIZE && t[i + 1] == CHAR_FULL)
		connected += 1;
	if (connected > 1)
		*connections = 1;
	if (!connected)
		return (0);
	return (1);
}
