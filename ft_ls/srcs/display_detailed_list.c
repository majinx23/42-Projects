/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_detailed_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 03:09:19 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/21 23:31:35 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** print list with -l option
*/

int		display_detailed_list(t_file *lst, int flags)
{
	int	size[6];
	int	total;
	int	first;

	ft_bzero(size, sizeof(size));
	total = 0;
	first = 1;
	get_row_size(lst, size, &total);
	while (lst)
	{
		if (first == 1 && !(flags & LS_D))
		{
			ft_printf("total %d\n", total);
			first = 0;
		}
		display_list_items(lst, size, flags);
		lst = lst->next;
	}
	return (1);
}

/*
** function to calculate row size
*/

int		get_row_size(t_file *file, int size[6], int *total)
{
	int	len;

	size[4] = 3;
	size[5] = 3;
	while (file)
	{
		size[0] = MAX(integer_len(file->st_nlink), size[0]);
		size[1] = MAX(ft_strlen(getpwuid(file->st_uid)->pw_name), size[1]);
		size[2] = MAX(ft_strlen(getgrgid(file->st_gid)->gr_name), size[2]);
		if (!S_ISCHR(file->mode))
			len = integer_len(file->st_size);
		else
		{
			size[4] = MAX(integer_len(major(file->st_rdev)), size[4]);
			size[4] = MAX(integer_len(minor(file->st_rdev)), size[4]);
			len = size[4] + 2 + size[5];
		}
		size[3] = MAX(len, size[3]);
		*total += file->st_blocks;
		file = file->next;
	}
	if (size[4] + size[5] + 1 < size[3])
		size[4] = size[3] - size[5] - 1;
	return (1);
}
