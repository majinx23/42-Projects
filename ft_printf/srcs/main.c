/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:38 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/12 12:14:14 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Credit : Many thanks to R. Monnier for the test file.
*/

#include "../incl/ft_printf.h"

# include <stdio.h>
# include <locale.h>

int		main(int ac, char **av)
{
	int		n;
	int		m;
	int		i;
	int		j;
	unsigned char	k;
	int		i1;
	int		i2;
	char	*str;
	char	c;

	setlocale(LC_ALL, "");
	(void)ac;

	printf("--16 en hexa--\n");
	i = ft_printf("Mon printf  : %x\n", 16);
	j = printf("Vrai printf : %x\n", 16);
	printf("Moi %d Le vrai : %d\n", i, j);


	printf("\n--et -16 en hexa--\n");
	n = -16;
	i = ft_printf("Mon printf  : %x\n", n);
	j = printf("Vrai printf : %x\n", n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n--13 et 16 en hexa--\n");
	n = 16;
	m = 13;
	i = ft_printf("Mon printf  : %x et %x\n", m, n);
	j = printf("Vrai printf : %x et %x\n", m, n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n--13 et 15 en hexa--\n");
	n = 15;
	m = 13;
	i = ft_printf("Mon printf  : %x et %X\n", m, n);
	j = printf("Vrai printf : %x et %X\n", m, n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n--intmax en hex--\n");
	n = 2147483647;
	i = ft_printf("Mon printf  : %x\n", n);
	j = printf("Vrai printf : %x\n", n);
	printf("Moi %d Le vrai : %d\n", i, j);


	printf("\n--intmax avec %%hlhx en hex--\n");
	n = 2147483647;
	i = ft_printf("Mon printf  : %hlhx\n", n);
	j = printf("Vrai printf : %hlhx\n", n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n--unsigned char 128 en hex--\n");
	k = 128;
	i = ft_printf("Mon printf  : %hhx\n", k);
	j = printf("Vrai printf : %hhx\n", k);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n--%%--\n");
	i = ft_printf("Mon printf  : %%\n");
	j = printf("Vrai printf : %%\n");
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n--pointeur--\n");
	i = ft_printf("Mon printf  : %p\n", &k);
	j = printf("Vrai printf : %p\n", &k);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- %%l15d --\n");
	n = 2147483647;
	i = ft_printf("Mon printf  : %15d\n", 2147483647);
	j = printf("Vrai printf : %15d\n", 2147483647);
	printf("Moi %d Le vrai : %d\n", i, j);
/*
	printf("\n-- invalid identifier --\n");           //     A REVOIR
	j = printf("Vrai printf : %010y\n");
	i = ft_printf("Mon printf  : %010y\n");
	printf("Moi %d Le vrai : %d\n", i, j);
*/
	printf("\n-- %%n --\n");
	j = printf("Vrai printf : %5n\n", &i2);
	printf("%d\n", i2);
	i = ft_printf("Mon printf  : %5n\n", &i1);
	printf("%d\n", i1);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- int with + and precision --\n");
	n = 13;
	i = ft_printf("Mon printf  : %+.5d\n", n);
	j = printf("Vrai printf : %+.5d\n", n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- int with 0 and precision --\n");
	n = 13;
	i = ft_printf("Mon printf  : %0.5d\n", n);
	j = printf("Vrai printf : %0.5d\n", n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- int with 0 and width --\n");          // REVOIR
	n = 13;
	i = ft_printf("Mon printf  : %05d\n", n);
	j = printf("Vrai printf : %05d\n", n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- X with # --\n");
	n = 13;
	i = ft_printf("Mon printf  : %#X\n", n);
	j = printf("Vrai printf : %#X\n", n);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- ld puis Ld avec int int int --\n");
	n = 13;
	i = ft_printf("Mon printf  : %ld et %Ld\n", 10, 11, 12);
	j = printf("Vrai printf : %ld et %Ld\n", 10, 11, 12);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- test --\n");
	n = 13;
	i = ft_printf("");
	j = printf("");
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- string --\n");
	str = "Félin";
	i = ft_printf("Mon printf  : %s\n", str);
	j = printf("Vrai printf : %s\n", str);
	printf("Moi %d Le vrai : %d\n", i, j);
/*
	printf("\n-- character --\n");                     //   REVOIR
	c = 'z';
	i = ft_printf("Mon printf  : %c\n", c);
	j = printf("Vrai printf : %c\n", c);
	printf("Moi %d Le vrai : %d\n", i, j);
*/
	printf("\n-- string unicode --\n");
	i = ft_printf("Mon printf  : %S\n", L"élodie");
	j = printf("Vrai printf : %S\n", L"élodie");
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- %% tout seul --\n");
	i = ft_printf("%");
	j = printf("%");
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- %%+n --\n");                          //  REVOIR
	i = ft_printf("%+10.0d\n", 0);
	j = printf("%+10.0d\n", 0);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- %%f --\n");                            // REVOIR
	i = ft_printf("{%f}{%F}\n", 1.42, 1.42);
	j = printf("{%f}{%F}\n", 1.42, 1.42);
	printf("Moi %d Le vrai : %d\n", i, j);

	printf("\n-- %%Lf --\n");                       //  REVOIR
	long double ld = 46.646;
	i = ft_printf("{%f}\n{%F}\n", 1444565444646.6465424242242, 1444565444646.6465424242242);
	j = printf("{%f}\n{%F}\n", 1444565444646.6465424242242, 1444565444646.6465424242242);
	printf("Moi %d Le vrai : %d\n", i, j);
/*
	printf("\n-- %%S 414 --\n");                  //      REVOIR infinite loop
	i = ft_printf("%lc\n", 414);
	j = printf("%lc\n", 414);
	printf("Moi %d Le vrai : %d\n", i, j);
	*/
}