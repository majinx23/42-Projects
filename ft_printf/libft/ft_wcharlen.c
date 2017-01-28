/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 00:03:43 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 18:47:57 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** returns the number of bytes used by wchar
*/

size_t	ft_wcharlen(unsigned c)
{
	if (c < 0x80)
		return (1);
	else if (c < 0x800)
		return (2);
	else if (c < 0x10000)
		return (3);
	return (4);
}
