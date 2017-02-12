/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_identical_nodes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:53:14 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/12 12:02:40 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** function to remove all values that are in both list by pair.
** credit : jfortin42 for the idea.
*/

#include "libft.h"

static void	free_and_point_to_next(t_list *c, t_list *d)
{
	t_list	*t;
	t_list	*u;

	t = c->next;
	u = d->next;
	c->content = NULL;
	d->content = NULL;
	c ? free(c) : 0;
	d ? free(d) : 0;
	c = t;
	d = u;
}

void		ft_remove_identical_nodes(t_list **a, t_list **b)
{
	t_list	*c;
	t_list	*d;

	d = *b;
	while (d)
	{
		c = *a;
		while (c)
		{
			if (c->content == d->content)
			{
				*a = (*a)->next;
				*b = (*b)->next;
				c = NULL;
				d = NULL;
				free_and_point_to_next(c, d);
			}
			else if (c->next && d->next && c->next->content == d->next->content)
				free_and_point_to_next(c->next, d->next);
			else if (d->next && c->content == d->next->content)
			{
				*a = (*a)->next;
				free_and_point_to_next(c, d->next);
			}
			else if (c->next && c->next->content == d->next)
			{
				*b = (*b)->next;
				free_and_point_to_next(c->next, d);
			}
			c = (c == NULL) ? *a: c->next;
		}
		d = (d == NULL) ? *b : d->next;
	}
}
