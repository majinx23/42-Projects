/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:56:47 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/05 17:09:02 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_findfd(t_list **begin, int fd)
{
	t_list	*tmp;

	tmp = *begin;
	if (tmp)
	{
		while (tmp)
		{
			if (fd == (int)tmp->content_size)
				return (tmp);
			tmp = tmp->next;
		}
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(begin, tmp);
	return (tmp);
}

int				get_next_line(int const fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static t_list	*list = NULL;
	t_list			*begin;
	char			*copy;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	begin = list;
	list = ft_findfd(&begin, fd);
	while (!ft_strchr(list->content, '\n') && (ret = read(fd, buf, BUFF_SIZE)))
		list->content = ft_strnjoinfree(list->content, buf, ret, 'L');
	ret = 0;
	while (((char*)list->content)[ret] && ((char*)list->content)[ret] != '\n')
		++ret;
	*line = ft_strndup(list->content, ret);
	if (((char*)list->content)[ret] == '\n')
		++ret;
	copy = list->content;
	list->content = ft_strdup(list->content + ret);
	free(copy);
	list = begin;
	return (ret ? 1 : 0);
}
