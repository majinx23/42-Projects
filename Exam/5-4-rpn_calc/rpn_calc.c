/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 14:27:22 by jwalsh            #+#    #+#             */
/*   Updated: 2016/12/04 18:55:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"


void	rpn_calc(char *s)
{
	t_s	**stack;
	int	num1;
	int	num2;

	if (!(stack = (t_s **)malloc(sizeof(t_s*))))
		return ;
	while (*s)
	{
		while (*s && is_space(*s))
			s++;
		if (is_digit(*s))
		{
			push(stack, atoi(s));
			//printf("check1\n");
			//printf("Added number: %i\n", (*stack)->i;
			while (*s && is_digit(*s))
				s++;
		}
		else if (is_op(*s))
		{
			if (*(s + 1) && is_digit(*(s + 1)))
			{
				push(stack, atoi(s));
				s++;
				while (*s && is_digit(*s))
					s++;
			}
			else{
				num1 = pop(stack);
				num2 = pop(stack);
				//printf("PRE-OP: num1: %i\n        num2: %i\n", num1, num2);
				if (num2 == 0 && (*s == '/' || *s == '%'))
				{
					printf("Error\n");
					return ;
				}
				push(stack, do_op(num1, num2, *s));
				//printf("do_op result: %i\n", (*stack)->i);
				//break;
				
				s++;
			}
		}
	}
	printf("%i\n", (*stack)->i);
	
}

void	push(t_s **stack, int i)
{
	//printf("begin push\n");
	t_s	*link;

	if (!(link = (t_s *)malloc(sizeof(t_s))))
		return ;
	link->i = i;
	if (*stack)
	{
		link->next = *stack;
		*stack = link;
		//printf("*stack = link\n");
	}
	else
	{
		link->next = *stack;
		stack = &link;
	}
	//printf("push end. *stack->i: %i\n", (*stack)->i);
}

int		pop(t_s **stack)
{
	//printf("begin pop\n");
	int	num;
	t_s *tmp;

	num = (*stack)->i;
	//printf("found i: %i\n", (*stack)->i);
	//printf("next num: %i\n", (*stack)->next->i);
	tmp = (*stack);
	*stack = (*stack)->next;
	free(tmp);
	return (num);
}

int	do_op(int i, int j, char c)
{
	if (c == '+')
		return (i + j);
	else if (c == '-')
		return (i - j);
	else if (c == '*')
		return (i * j);
	else if (c == '/')
		return (i / j);
	else if (c == '%')
		return (i % j);
	return (0);
}
