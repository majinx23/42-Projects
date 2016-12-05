/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 21:56:35 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/04 22:45:27 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}

int		ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		r_size(char *s)
{
	unsigned int n;
	unsigned int i;

	n = 0;
	i = 0;
	while (s[i])
		if (!ft_isblank(s[i++]) && (!n || ft_isblank(s[i - 2])))
			++n;
	return (n);
}

char	**ft_strsplit(char *s)
{
	int		i = 0;
	int		j = 0;
	char	**r;
	int		w_len = 0;
	int		r_len = r_size(s);

	if (!(r = (char **)malloc(sizeof(char *) * (r_len + 1))))
		return (0);
	while (*s && r_len--)
	{
		while (ft_isblank(*s))
			++s;
		while (*s && !ft_isblank(*s))
		{
			++s;
			++w_len;
		}
		if (!(r[i] = (char *)malloc(sizeof(char) * (w_len + 1))))
			return (0);
		j = 0;
		while (w_len)
			r[i][j++] = *(s - w_len--);
		r[i++][j] = '\0';
	}
	return (r);
}

void	rev_wstr(char *s)
{
	char	**r = ft_strsplit(s);
	int		n = r_size(s);

	while (n--)
	{
		ft_putstr(r[n]);
		if (n)
			ft_putstr(" ");
	}
	free((char **)r);
	r = NULL;
}

int		main(int ac, char **av)
{
	if (ac == 2 && *av[1])
		rev_wstr(av[1]);
	write(1, "\n", 1);
	return (0);
}
