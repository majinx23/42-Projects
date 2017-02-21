/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 13:18:29 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/22 00:23:59 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function to detect flag
*/

int			parsing(int ac, char **av, int *flags)
{
	int	i;

	*flags = 0;
	i = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		if (av[i][1] == '-' && av[i][2])
			return (i + 1);
		if (!parse_options(av[i], flags))
			return (-1);
	}
	return (i);
}

/*
** here we light the nth bit according to the parsed flag
** for example if we have -Ra then we will have flags equal to 0b101
** the user decides which options he wants :
** 1) a for hidden files and folders
** 2) l for details
** 3) R to recursively display subfolders content
** 4) r to order by creation date
** 5) t to order by timestamp
** 6) d to display only current directory
** 7) -1 \n to display only in 1 column
** nb : *flags &= (*s == 'l') ? ~128 : ~2; is to set to 0 l if 1 was found
** and reversely .
*/

int		parse_options(char *s, int *flags)
{
	while (*(++s))
	{
		if (*s == 'a')
			*flags |= LS_A;
		else if (*s == 'R')
			*flags |= LS_RR;
		else if (*s == 'r')
			*flags |= LS_R;
		else if (*s == 't')
			*flags |= LS_T;
		else if (*s == 'd')
			*flags |= LS_D;
		else if (*s == 'G')
			*flags |= LS_G;
		else if ((*s == 'l') || (*s == '1'))
		{
			*flags |= (*s == 'l') ? LS_L : LS_ONE;
			*flags &= (*s == 'l') ? ~LS_ONE : ~LS_L;
		}
		else
			ls_error(s, USAGE);
	}
	if (*flags & LS_A || *flags & LS_R || *flags & LS_RR || *flags & LS_T)
		*flags |= LS_ONE;
	return (1);
}

/*
** function to handle errors
** 0 : display usage for invalid flag, -1 : errno, -2 : mall_err
*/

int		ls_error(char *s, int error)
{
	if (error == USAGE)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(*s, 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage: ft_ls [-alRrtdG1] [file ...]", 2);
	}
	else if (error == ERRNO || error == MALL_ERR)
		ft_putstr_fd("ft_ls: ", 2);
	if (error == ERRNO)
	{	
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (error == ERRNO)
		ft_putendl_fd(strerror(errno), 2);
	if (error == USAGE || error == MALL_ERR)
		exit(EXIT_FAILURE);
	return (0);
}
