/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 14:29:11 by jwalsh            #+#    #+#             */
/*   Updated: 2016/12/04 15:57:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"

int	is_op(int c)
{
	return (c == '+' ||
			c == '-' ||
			c == '*' ||
			c == '/' ||
			c == '%');
}

int	is_digit(int c)
{
	return ('0' <= c && c <= '9');
}

int	is_space(int c)
{
	return (c == 32);
}
