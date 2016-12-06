/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:53:51 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/06 18:41:23 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_atoi_nc(char *s)
{
	int		r;

	r = 0;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + *s++ - '0';
	return (r);
}

int		is_prime(int n)
{
	int i;

	i = 2;
	while (i < n)
		if (n % i++ == 0)
			return (0);
	return (1);
}

void	add_prime_sum(int n)
{
	int	i;

	if (n == 1)
		ft_putchar('1');
	i = 1;
	while (n >= i)
	{
		if (is_prime(i))
		{
			n /= i;
			ft_putchar(i + '0');
			i = n - 1;
		}
		++i;
	}
}

int		main(int ac, char **av)
{
	if (ac == 2 && ft_atoi_nc(av[1]) > 0)
		add_prime_sum(ft_atoi_nc(av[1]));
	else
		write(1, "0", 1);
	write(1, "\n", 1);
	return (1);
}
