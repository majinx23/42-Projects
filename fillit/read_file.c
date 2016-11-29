/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:59:21 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 16:11:38 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Reads the file and resturns a string with its contents.
*/

char	*read_file(char *av)
{
	char	buf[MAX_BUFFER_SIZE + 1];
	int		fd;
	int		ret;
	char	*result;

	if ((fd = open(av, O_RDONLY)) == -1)
		return (NULL);
	if ((ret = read(fd, &buf, MAX_BUFFER_SIZE + 1)) == -1)
		return (NULL);
	if (!(result = ft_memalloc(sizeof(char) * (MAX_BUFFER_SIZE + 1))))
		return (NULL);
	buf[ret] = '\0';
	ft_memmove(result, buf, ret + 1);
	close(fd);
	return (result);
}
