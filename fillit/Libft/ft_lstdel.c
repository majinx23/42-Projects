/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:07:32 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:00:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Frees the memory of the link pointed to by the first param,
** and that of all succeeding links using del and free.
** The pointer to the first link becomes NULL.
*/

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*p;

	if (!alst)
		return ;
	p = *alst;
	while (p != NULL)
	{
		del(p->content, p->content_size);
		free(p);
		p = p->next;
	}
	*alst = NULL;
}
