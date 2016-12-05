/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 20:08:36 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/04 23:55:50 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>

// gcc checkmate.c && ./a.out '..Q.' '...K' '....' '....' | cat -e
// B = 3      Rook = 2 and Queen == 6   an P == 1

int		checkmate(int ac, char **av)
{
	int		y = 1;
	int		x = 0;
	int		len = 0;
	int		b = 0;
	int		a = 0;
	char	**m;

	while (ac-- > 1)
		len++;
	if (!(m = (char **)malloc(sizeof(char *) * len * (len + 1))))
		return (0);
	y = 0;
	while (y < len)
	{
		if (!(m[y] = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		x = 0;
		while (*av[y + 1] && av[y + 1][x])
		{
			m[y][x] = av[y + 1][x];
			if (m[y][x] == 'K')
			{
				a = x;
				b = y;
			}
			++x;
		}
		m[y][x] = 0;
		++y;
	}

	if (m[b + 1][a + 1] == 'P' || m[b + 1][a - 1] == 'P')
		return (0);
	y = 1;
	x = a;
	while (y < len)
	{
		if (m[y][x] == 'R' || m[y][x] == 'Q')
			return (0);
		if (m[y + 1][x + (y + 1 - b)] == 'B' ||
				m[y + 1][x + (b - y - 1)] == 'B' ||
				m[y - 1][x + (y + 1 - b)] == 'B' ||
				m[y - 1][x + (b - y - 1)] == 'B')
			return (0);
		if (m[y + 1][x + (y + 1 - b)] == 'Q' ||
				m[y + 1][x + (b - y - 1)] == 'Q' ||
				m[y - 1][x + (y + 1 - b)] == 'Q' ||
				m[y - 1][x + (b - y - 1)] == 'Q')
			return (0);
		++y;
	}

	y = b;
	x = 0;
	while (x < len)
	{
		if (m[y][x] == 'R' || m[y][x] == 'Q')
			return (0);
		++x;
	}

	// print map and solution
	y = 0;
	while (y < len)
	{
		write(1, m[y], len);
		write(1, "\n", 1);
		++y;
	}
	return (1);
}

int		main(int ac, char **av)
{
	if (ac > 1 && checkmate(ac, av))
		write(1, "Success", 7);
	else
		write(1, "Fail", 4);
	write(1, "\n", 1);
	return (0);
}
