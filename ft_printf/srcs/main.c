/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:38 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 20:01:32 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

int		main(void)
{
	int					chiffre;
	int					nombre;
	unsigned long long	a;
	long long			c;
	int					b;
	long double			f;
	int					accuracy;

	setlocale(LC_ALL, "");
	nombre = 12345;
	chiffre = 9;
	//ft_putstr("\033[36m");
	//ft_printf("%{red}red %{yellow}yellow %{green}green %{cyan}cyan %{blue}blue %{purple}purple %{pink}pink %{eoc}End of color.\n");
	ft_printf("Hello ! my name is%5.4s and I'm %d%% cool %ls %p\n", "Neilyroth", 100, L"|-\u4E2A-|", &chiffre);
	   printf("Hello ! my name is%5.4s and I'm %d%% cool %ls %p\n", "Neilyroth", 100, L"|-\u4E2A-|", &chiffre);
	ft_printf("%c|%c|%lc\n", 'H', 'i', L'\u4E2A');
	   printf("%c|%c|%lc\n", 'H', 'i', L'\u4E2A');
	a = 57;
	b = 16;
	b = 10;
	c = 5;
	f = -6456454556.596985658;
	printf("\n\n");
	printf("printf(%%llu, -0x2); %llu_pf", a);
	printf("   %s", ft_ulltoa_base((unsigned long long)a, b, 0));

	printf("\n\n");
	printf("printf(%%lu , -0x2);  %lu_pf", (unsigned long)a);
	printf("   %s", ft_ulltoa_base((unsigned long)a, b, 0));

	printf("\n\n");
	printf("printf(%%x  , 0xffffffff);  %x_pf", 0xffffffff);
	printf("   %s", ft_ulltoa_base(0xffffffff, 16, 0));
	printf("\n\n");

	printf("printf(%%lld, -2);  %lld_pf", c);
	printf("   %s", ft_lltoa_base((long long)c));
	printf("\n\n");

	printf("printf(%%d  , 0xffffffff);  %d_pf", (int)c);
	printf("   %s", ft_lltoa_base((int)c));
	printf("\n\n");

	accuracy = 0;
	if (!accuracy)
		accuracy = 6;
	printf("printf(%%f  , 14.647);  %.6f", (double)f);
	printf("   %s", ft_ldtoa((double)f, accuracy));
	printf("\n\n");

	printf("printf(%%lf  , 14.647);  %.6Lf", f);
	printf("   %s", ft_ldtoa(f, accuracy));
	printf("\n\n");
	return (0);
}

void	msg_die(char *message)
{
	ft_putstr("\033[31m");
	ft_putendl(message);
	exit(1);
}
