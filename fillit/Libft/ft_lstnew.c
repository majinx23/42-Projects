/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:37:26 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:03:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocated memory for and returns a new link with the content and
** content size passed as parameters.
*/

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;
	void	*new_content;

	if (!(new_content = ft_memalloc(content_size)))
		return (NULL);
	if (!content)
	{
		new_content = NULL;
		content_size = 0;
	}
	else
		ft_memcpy(new_content, content, content_size);
	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	list->content = new_content;
	list->content_size = content_size;
	list->next = NULL;
	return (list);
}
