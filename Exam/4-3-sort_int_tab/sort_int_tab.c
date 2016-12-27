/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 07:33:39 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/27 20:09:43 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	*a += *b;
	*b = *a - *b;
	*a -= *b;
}

void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned	a = 0;
	unsigned	i = 0;

	while (++i < size)
	{
		if (tab[i - 1] > tab[i])
		{
			ft_swap(&tab[i - 1], &tab[i]);
			a = i;
		}
		while (--a)
		{
			a = (tab[a - 1] > tab[a]) ? a : 0;
			a ? ft_swap(&tab[a - 1], &tab[a]) : 0;
		}
	}
}
