/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 19:11:48 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/27 19:14:22 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		check_RGB_validity(char *s)
{
	unsigned	len;

	len = 0;
	while (*s && (ft_isdigit(*s) || (*s >= 'A' && *s <= 'F')
				|| (*s >= 'a' && *s <= 'f')))
	{
		++len;
		if (len > 8)
			return (0);
		++s;
	}
	return (len);
}

int		check_digit_validity(char *s, unsigned i)
{
	unsigned	t;
	unsigned	j;

	j = 0;
	if (!i || ((s[j - 1]) == ' ') || (s[j - 1] == '-'))
		++j;
	else
		return (0);
	while (s[j] && ft_isdigit(s[j]))
		++j;
	if (s[j] == ',')
	{
		if (s[j + 1] && s[j + 2] && s[j + 1] == '0' && s[j + 2] == 'x')
		{
			t = (j += 2);
			j += check_RGB_validity(s + j);
			if (t == j)
				return (0);
		}
		else
			return (0);
	}
	return (j);
}

int		check_validity(char *s)
{
	unsigned	i;
	unsigned	x_len;
	unsigned	t;

	i = 0;
	x_len = 0;
	while (s[i] && s[i] != '\n')
	{
		if (ft_isdigit(s[i]))
		{
			if (!(t == (check_digit_validity(s + i, i))))
				return (0);
			++x_len;
			i += t;
		}
		else if (s[i] == '-' && ((s[i - 1] && s[i - 1] == ' ') || !i) &&
				(s[i + 1] && ft_isdigit(s[i - 1])))
			++i;
		else if (s[i] != ' ')
		{
			return (0);
			++i;
		}
	}
	return (x_len);
}
