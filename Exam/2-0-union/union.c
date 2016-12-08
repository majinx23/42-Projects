/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 16:16:51 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/08 16:14:18 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_cmp(char c, char *s, int index)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	if (i == index)
		write(1, &s[i], 1);
}

void	union(char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	while (s1[++i])
		ft_cmp(s1[i], s1, i);
	i = 0;
	while (s2[i])
	{
		j = -1;
		while (s1[j++])
			if (s2[i] == s1[j])
				break ;
		if (!s1[j])
			ft_cmp(s2[i], s2, i);
		i++;
	}
}

int		main(int ac, char **av)
{
	if (argc == 3)
		union(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}

int		check(char *s1, int i)
{
	int a;

	a = 0;
	while (a < i)
	{
		if (s1[a] == s1[i])
			return (0);
		++a;
	}
	return (1);
}

void	union(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (check(s1, i))			
		{
			while (*s2)
			{
				if (s1[i] == *s2++)
				{
					write(1, s2 - 1, 1);
					break;
				}
			}
		}
		++i;
	}
}
