/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 19:11:48 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/29 21:53:02 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 ** converts color from base hexa to base 10

static	int		ft_htoi(char *s)
{
	int n;

	n = 0;
	while (*s)
	{
		n *= 16;
		if (*s >= 'A' && *s <= 'F')
			n += *s - 'A' + 10;
		else
			n += ft_isdigit(*s) ? *s -'0' : *s - 'a' + 10;
		++s;
	}
	return (n);
}


 ** checks that color is valid and stocks it into *d->c
 */

static t_bool	check_RGB_validity(char *s, unsigned *i)
{
	size_t		n;

	n = 0;
	while (s[*i + n] && (ft_isdigit(s[*i + n]) || (s[*i + n] >= 'A' &&
				s[*i + n] <= 'F') || (s[*i + n] >= 'a' && s[*i + n] <= 'f')))
		++n;
	if (n > 8)
		return (False);
	*i += n;
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
