/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 13:18:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/21 01:51:43 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*init_files_list(char **names_list, int size, int options, int first)
{
	t_file	*begin;
	int		i;

	begin = NULL;
	(!size) ? add_new_file("", ".", &begin) : ft_sort_tab(names_list, size, &ft_strcmp);
	i = -1;
	while (++i < size)
		if (add_new_file("", names_list[i], &begin) == -1 && first)
			ls_error(names_list[i], ERRNO);
	sort_list(&begin, options);
	return (begin);
}

/*
** main program http://man7.org/linux/man-pages/man1/ls.1.html
** check parsing.c for function parsing
*/

int				main(int ac, char **av)
{
	int			i;
	int			flags;
	t_file		*begin;
	int			no_files;

	if ((i = parsing(ac, av, &flags)) == -1)
		return (1);
	av += i;
	ac -= i;
	begin = init_files_list(av, ac, flags, 1);
	only_files(&begin);
	no_files = (!begin ? 1 : 0);
	display_list(&begin, (flags | LS_D));
	free_list_content(&begin);
	begin = init_files_list(av, ac, flags, 0);
	print_folders(begin, flags, (!no_files ? 1 : 2), ac);
	free_list_content(&begin);
	return (0);
}
