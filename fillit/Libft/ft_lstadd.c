/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:23:42 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:00:07 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new element to the front of the list.
*/

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *n)
{
	if (n)
	{
		n->next = *alst;
		*alst = n;
	}
}
