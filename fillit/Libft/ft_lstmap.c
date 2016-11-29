/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:31:38 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 18:04:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Traverses the list applying to each link the function f.
** Creates a new list with malloc with the results of the function
** If an allocation fails, returns NULL.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	if (!(new = f(lst)))
		return (NULL);
	new->next = ft_lstmap(lst->next, f);
	return (new);
}
