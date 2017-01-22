/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 11:52:52 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 16:24:58 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		printmap(t_3d *d)
{
	unsigned x;
	unsigned y = 0;
	while (y < d->max.y)
	{
		x = 0;
		while (x < d->max.x)
		{
			ft_putnbr(d->m[y][x].z);
			ft_putstr(" 0x");
			ft_puthex(d->c[y][x]);
			ft_putchar(' ');
			++x;
		}
		ft_putchar('\n');
		++y;
	}
	return (1);
}
