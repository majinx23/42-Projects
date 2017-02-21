/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_folders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 17:06:45 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/22 00:04:40 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** reads folder content
*/

static t_file	*read_folder(char path[PATH_MAX], char *name, int options)
{
	t_file			*begin;
	DIR				*folder;
	struct dirent	*entry;

	begin = NULL;
	if (!(folder = opendir(path)))
		ls_error(name, 0);
	else if (!(options & LS_D))
	{
		while ((entry = readdir(folder)))
			if (entry->d_name[0] != '.' || (options & LS_A))
				add_new_file(path, entry->d_name, &begin);
	}		
	else
		add_new_file(path, ".", &begin);
	if (folder)
		closedir(folder);
	return (begin);
}

static void 	print_folder_name(char *full_path, int number, int *first)
{
	if (number != 0 && number != 1 && *first == 2)
	{
		*first = 1;
		ft_printf("%s:\n", full_path);
	}
	else if (number != 0 && number != 1)
		ft_printf("\n%s:\n", full_path);
}

/*
** display folders and content
*/

int				print_folders(t_file *begin, int flags, t_bool empty, int n)
{
	t_file			*file;

	file = begin;
	if (!(flags & LS_RR) && !empty)
		return (1);
	while (file)
	{
		if (S_ISDIR(file->mode) &&
			(empty || (ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))))
		{
			print_folder_name(file->full_path, n, &empty);	
			begin = read_folder(file->full_path, file->name, flags);
			if (begin)
			{
				display_list(&begin, flags);
				print_folders(begin, flags, 0, -1);
				free_list_content(&begin);
			}
		}
		file = file->next;
	}
	return (1);
}
