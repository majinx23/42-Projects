/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 21:43:06 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/03 22:03:34 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_list
{
	int				data;
	struct s_list	*next;
}				t_list;

int		ascending(int a, int b)
{
	return (a <= b);
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
	t_list	*tmp;

	tmp = lst;
	while (lst->next)
		if (((*cmp)(lst->data, lst->next->data)) == 0)
			ascending(lst->data, lst->next->data);
	lst = tmp;
	return (lst);
}
