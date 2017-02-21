/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 03:10:19 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/21 03:10:22 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** listing by ascii order if no -r flag
*/

t_file *reverse_lst(t_file *lst)
{
	t_file *a;
	t_file *b;
	t_file *c;

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

/*
** for -r flag
*/

/*
static t_file	*lst_sort_ascii(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
		lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_ascii(lst->next);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_ascii(lst->next);
	}
	return (lst);
}
*/

/*
static t_file		lst_sort_ascii(t_file *lst)
{
	t_file	*tmp;
	t_file		*item;
	t_file		*tmp_item1;
	t_file		*tmp_item2;

//	first = ft_lstd_get_first(lst);
	while (lst)
	{
		tmp = NULL;
		while (tmp)
		{
			tmp_item1 = lst->name;
			tmp_item2 = tmp->name;
			if (tmp_item1 && tmp_item2
				&& ft_strcmp(tmp_item1->name, tmp_item2->name) < 0)
			{
				item = tmp->name;
				tmp->name = lst->name;
				lst->name = item;
			}
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	return (lst);
}
*/



static t_file    *lst_sort_ascii(t_file *lst)
{
    if (!lst)
        return (NULL);
    if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
        lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_ascii(lst->next);
    if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
    {
        lst = lst_swap(lst, lst->next);
        lst->next = lst_sort_ascii(lst->next);
    }
    return (lst);
}


static t_file	*lst_sort_rev_ascii(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) < 0)
		lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_rev_ascii(lst->next);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) < 0)
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_rev_ascii(lst->next);
	}
	return (lst);
}

/*
** for -rt flag
*/

static t_file	*lst_sort_rev_time(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && (lst->time > lst->next->time))
		lst = lst_swap(lst, lst->next);
	else if (lst->next && lst->time == lst->next->time)
		if (lst->next && (lst->ntime < lst->next->ntime))
			lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_rev_time(lst->next);
	if (lst->next && (lst->time > lst->next->time))
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_rev_time(lst->next);
	}
	else if (lst->next && lst->time == lst->next->time)
	{
		if (lst->next && (lst->ntime < lst->next->ntime))
		{
			lst = lst_swap(lst, lst->next);
			lst->next = lst_sort_rev_time(lst->next);
		}
	}
	return (lst);
}

/*
** for -t flag
*/

static t_file	*lst_sort_time(t_file*lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && (lst->time < lst->next->time))
		lst = lst_swap(lst, lst->next);
	else if (lst->next && lst->time == lst->next->time)
		if (lst->next && (lst->ntime < lst->next->ntime))
			lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_time(lst->next);
	if (lst->next != NULL && (lst->time < lst->next->time))
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_time(lst->next);
	}
	else if (lst->next && lst->time == lst->next->time)
	{
		if (lst->next && (lst->ntime < lst->next->ntime))
		{
			lst = lst_swap(lst, lst->next);
			lst->next = lst_sort_time(lst->next);
		}
	}
	return (lst);
}

/*
** sorting list according to r and t parameters
*/

int				sort_list(t_file **begin, short flags)
{
//	int reverse;
//	t_file *tmp;

//	tmp = NULL;
//	reverse = 1;
	*begin =(flags & LS_R) ? lst_sort_rev_ascii(*begin) : lst_sort_ascii(*begin);
//	*begin = lst_sort_ascii(*begin;
/*	while (*begin)
	{
		ft_putendl((*begin)->name);
		*begin = (*begin)->next;
	}
*/	
//	*begin = tmp;
	if (flags & LS_T)
		*begin = (flags & LS_R) ? lst_sort_rev_time(*begin) : lst_sort_time(*begin);
	//if (reverse)
//			*begin = reverse_lst(*begin);
	return (1);
}
