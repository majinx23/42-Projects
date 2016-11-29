/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:25:46 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/10 15:32:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Frees the string pointed to by as, and assigns its pointer to NULL.
*/

#include "libft.h"

void	ft_strdel(char **as)
{
	if (!as || !(*as))
		return ;
	free(*as);
	*as = NULL;
}
