/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 17:06:31 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/21 03:10:00 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		lst_delone(t_file **file)
{
	ft_memdel((void**)&(*file)->name);
	ft_memdel((void**)file);
}

void			only_files(t_file **begin)
{
	t_file	*tmp;

	tmp = *begin;
	while (tmp != NULL && S_ISDIR(tmp->mode))
	{
		tmp = tmp->next;
		lst_delone(begin);
		*begin = tmp;
	}
	if (tmp != NULL)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		if (S_ISDIR(tmp->mode))
		{
			(*begin)->next = tmp->next;
			lst_delone(&tmp);
			tmp = (*begin)->next;
		}
		else
		{
			tmp = tmp->next;

			begin = &((*begin)->next);
		}
	}
}
