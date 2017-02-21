/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_folders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 17:06:45 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/21 03:10:32 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*read_folder(char path[PATH_MAX], char *name, int options)
{
	t_file			*begin;
	DIR				*dir;
	struct dirent	*entry;

	if (!(dir = opendir(path)))
	{
		ls_error(name, 0);
		return (NULL);
	}
	begin = NULL;
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.' || (options & LS_A))
			add_new_file(path, entry->d_name, &begin);
	}
	closedir(dir);
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

int				print_folders(t_file *begin, int options, t_bool first,
								int number)
{
	t_file			*file;

	file = begin;
	if (!(options & LS_RR) && !first)
		return (1);
	while (file)
	{
		if (S_ISDIR(file->mode) &&
			(first || (ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))))
		{
			print_folder_name(file->full_path, number, &first);
			begin = read_folder(file->full_path, file->name, options);
			if (begin)
			{
				display_list(&begin, options);
				print_folders(begin, options, 0, -1);
				free_list_content(&begin);
			}
		}
		file = file->next;
	}
	return (1);
}
