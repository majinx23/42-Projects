/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 22:36:30 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/04 23:29:07 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> //

/*
** Please email me if you find a shorter solution ;)
** (not the one using ternary inside ternary and removing the variable "sign")
*/

char	*ft_itoa_base(int value, int base)
{
	char	*s;
	long	n;
	int		sign;
	int		i;

	n = (value < 0) ? -1 * (long)value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	if (!(s = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	s[i] = '\0';
	n = (value < 0) ? -1 * (long)value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	s[i] = (sign == -1) ? '-' : s[i];
	return (s);
}

int		main(int ac, char **av)//
{//
	if (ac == 3)//
		printf("%s", ft_itoa_base(atoi(av[1]), atoi(av[2])));//
	return (1);//
}//
