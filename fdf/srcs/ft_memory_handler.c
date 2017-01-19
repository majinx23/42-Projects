/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:23:15 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/19 16:05:56 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int		malloc_map(t_3d *d)
{
	t_index		i;

	if (!(d->mm = (t_vector **)malloc(sizeof(t_vector *) * d->max.y)))
		return (0);
	i.y = 0;
	while (i.y < d->max.y)
	{
		if (!(d->mm[i.y] = (t_vector *)malloc(sizeof(t_vector) * d->max.x)))
			return (0);
		++i.y;
	}
	return (1);
}

void	free_matrix(float **m)
{
	int		i;

	i = -1;
	while (++i < 4)
		free(m[i]);
	free(m);
	(void)m;
}

void	free_all(t_3d *d)
{
	int		i;

	i = 0;
	d->matrix ? free_matrix(d->matrix) : 0;
	while (i < d->max.y)
	{
		d->m[i] ? free(d->m[i]) : 0;
		d->c[i] ? free (d->c[i]) : 0;
		d->mm[i] ? free(d->mm[i]) : 0;
		++i;
	}
	d->m ? free(d->m) : 0;
	d->mm ? free(d->mm) : 0;
	d->c ? free(d->c) : 0;
}
