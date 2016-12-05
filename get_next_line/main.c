/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:57:02 by angavrel          #+#    #+#             */
/*   Updated: 2016/11/30 11:57:05 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	i = 1;
	while (i <= argc)
	{
		if ((fd = open(argv[i++], O_RDONLY)) < 0 && argc == 1)
			fd = 0;
		while (get_next_line(fd, &line) == 1)
		{
			ft_putendl(line);
			free(line);
		}
	}
	return (0);
}
