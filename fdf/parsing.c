/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 19:11:48 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/28 18:47:26 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** checks that color is valid and stocks it into *d->c
*/

static t_bool	check_RGB_validity(char *s, unsigned *i)
{
	unsigned	len;

	len = 0;
	while (s[*i] && (ft_isdigit(s[*i]) || (s[*i] >= 'A' && s[*i] <= 'F')
				|| (s[*i] >= 'a' && s[*i] <= 'f')))
	{
		++len;
		if (len > 8)
			return (False);
		++*i;
	}
	return (True);
}

/*
** checks that digit is a valid one.
*/

static t_bool	check_digit_validity(char *s, unsigned *i)
{
	if (!*i || ((s[*i - 1]) == ' ') || (s[*i - 1] == '-'))
		++*i;
	else
		return (False);
	while (s[*i] && ft_isdigit(s[*i]))
		++*i;
	if (s[*i] == ',')
	{
		if (s[*i + 1] && s[*i + 2] && s[*i + 1] == '0' && s[*i + 2] == 'x')
		{
			*i += 3;
			if (check_RGB_validity(s, i) == False)
				return (False);
		}
		else
			return (False);
	}
	return (True);
}

/*
** checks that the map is a valid one with above functions' help
*/

unsigned		check_validity(char *s)
{
	unsigned	i;
	unsigned	x_len;

	i = 0;
	x_len = 0;
	while (s[i] && s[i] != '\n')
	{
		if (ft_isdigit(s[i]))
		{
			if (check_digit_validity(s, &i) == False)
				return (0);
			++x_len;
		}
		else if (s[i] == '-' && s[i + 1] && ft_isdigit(s[i + 1]))
			++i;
		else if (s[i] == ' ')
			++i;
		else
			return (0);
	}
	return (x_len);
}
