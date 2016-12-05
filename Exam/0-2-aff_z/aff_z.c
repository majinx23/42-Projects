/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_z.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 14:15:08 by angavrel          #+#    #+#             */
/*   Updated: 2016/11/15 21:35:56 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		main(int ac, char **av)
{
	int i;

	i = 0;
	if (ac != 2)
		ft_putchar('z');
	else
		while (av[1][i])
			if (av[1][i++] == 'z')
			{
				ft_putchar('z');
				ft_putchar('\n');
				return (0);
			}
	ft_putchar('\n');	
	return (0);
}
