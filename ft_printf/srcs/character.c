/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 19:20:44 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 00000000 -- 0000007F: 	0xxxxxxx
** 00000080 -- 000007FF: 	110xxxxx 10xxxxxx
** 00000800 -- 0000FFFF: 	1110xxxx 10xxxxxx 10xxxxxx
** 00010000 -- 001FFFFF: 	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

void	character(va_list ap, t_flags *flags)
{
	unsigned c;
	int len;

	c = va_arg(ap, unsigned);
	adjust_length(flags->min_length - 1, !flags->a_minus);
	len = ft_putwchar(c);
	adjust_length(flags->min_length - 1, flags->a_minus);
	return ;
}


