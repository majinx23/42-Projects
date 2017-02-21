/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 21:33:52 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/19 22:12:10 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct	s_lst
{
	struct s_lst *next;
	int		data;
}				t_lst;

t_lst *reverse_lst(t_lst *lst)
{
	t_lst *a;
	t_lst *b;
	t_lst *c;

	a = NULL;
	b = lst;
	c = (lst)->next;
	while (b)
	{
		c = b->next;
		b->next = a;
		a = b;
		b = c;
	}
	return (a);
}

int		main(void)
{
	t_lst *p;
	int	i;
	t_lst *begin;

	i = 0;
	p = (t_lst *)malloc(sizeof(t_lst));
	begin = p;
	while (i < 10)
	{
		p->data = i;
		++i;
		if (i < 10)
		{
			p->next = (t_lst *)malloc(sizeof(t_lst));
			p = p->next;
		}
	}
	p->next = NULL;
	begin = reverse_lst(begin);
	while (begin)
	{
		ft_putnbr(begin->data);
		begin = begin->next;
	}
}
