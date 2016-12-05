/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:33:35 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/05 20:17:27 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>


void	print_bits(unsigned char octet)
{
	int		i;

	i = 128;
	while (i)
	{
		if (octet < i)
			write(1, "0", 1);
		else
		{
			write(1, "1", 1);
			octet -= i;
		}
		i /= 2;
	}
}




int		main(int ac, char **av)
{
	if (ac == 2)
		print_bits(*av[1]);
	return (0);
}
