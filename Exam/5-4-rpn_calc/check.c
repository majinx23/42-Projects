/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 15:44:24 by jwalsh            #+#    #+#             */
/*   Updated: 2016/12/04 18:47:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"

int	check_input(char *s)
{
	int	num_c;
	int	op_c;

	num_c = 0;
	op_c = 0;
	while (*s)
	{
		if (!(is_op(*s) || is_digit(*s) || is_space(*s)))
		{
			printf("wrong char\n");
			return (0);
		}
		if (is_op(*s))
		{
			if (num_c && (*(s - 1) && !is_space(*(s - 1))))
				return (0);
			op_c++;
			//printf("op-c:%i\n", op_c);
			if ((*s == '-' || *s == '+') && is_digit(*(s + 1)))
				op_c--;
		}
		else if (is_digit(*s))
		{
			if (!num_c || !is_digit(*(s - 1)))
				num_c++;
		}
		if (is_space(*s) && num_c <= op_c)
		{
			//printf("num_c <= op_n\n");
			return (0);
		}
		s++;
	}
	if (is_space(*(s - 1)))
		return (0);
	printf("num_c: %i\nop-c: %i\n", num_c, op_c);
	return (num_c - op_c == 1 ? 1 : 0);
}
