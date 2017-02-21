/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 03:09:33 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/22 00:17:02 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** displays exactly as LIBC LS, from top to bottom and left to right instead of
** left to right and then top to bottom.
*/

static int		lst_column(t_file *lst, t_index row_col, int maxlen, int flags)
{
	int		tmp_column;
	int		tmp_row;
	t_file	*lst_tmp;
	int		counter;

	counter = row_col.y;
	while (lst && counter--)
	{
		tmp_column = row_col.x;
		lst_tmp = lst->next;
		while (lst && tmp_column--)
		{	
			display_name(lst, flags);
			if (tmp_column)
				ft_putnchar(MAX(maxlen - ft_strlen(lst->name), 0), ' ');
			tmp_row = row_col.y;
			while (lst && tmp_row--)
				lst = lst->next;	
		}
		ft_putchar('\n');
		lst = lst_tmp;
	}
	return (1);
}

/*
** bonus on columns
** padding is done according to the longest file name (maxlen)
** so we need to go through the list once in order to get it (tmp).
** if (!(flags & 128) checks for -1 option, row will be number of element.
*/

static int		display_basic_list(t_file *lst, int flags)
{
	int		maxlen;
	struct	ttysize ts;
	t_index	i;
	t_file	*tmp_lst;

	maxlen = lst_maxlen(lst) + ((flags & LS_G) ? 1 : 4);
	ioctl(0, TIOCGWINSZ, &ts);
	i.x = (!(flags & 128)) ? ts.ts_cols / maxlen : 1;
	i.y = 0;
	tmp_lst = lst;
	while (tmp_lst)
	{
		++i.y;
		tmp_lst = tmp_lst->next;
	}
	if (!(flags & 128))
		i.y = (i.y % i.x ? 1 : 0) + (i.y / i.x);
	lst_column(lst, i, maxlen, flags);
	return (1);
}

/*
** print list ordered as specified by user
*/

int				display_list(t_file **lst, int flags)
{
	sort_list(lst, flags);
	if (!(flags & LS_L))
		display_basic_list(*lst, flags);
	else
		display_detailed_list(*lst, flags);
	return (1);
}

/*
** sub function for norm and to handle -c color flag
*/

void		display_name(t_file *l, int flags)
{
	if (flags & LS_G)
	{
		if (S_ISDIR(l->mode))
			ft_printf("%{cyan}%s%{eoc}", l->name);
		else
			ft_printf((S_IXUSR & l->mode) ? "%{red}%s%{eoc}" : "%s", l->name);
	}	
	else
		ft_printf("%s", l->name);
}
