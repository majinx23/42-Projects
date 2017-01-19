/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 04:03:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 20:35:23 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
   Vous devez gérer les conversions suivantes : sSpdDioOuUxXcC
   • Vous devez gérer le %%
   • Vous devez gérer les flags #0-+ et espace
   • Vous devez gérer la taille minimum du champ
   • Vous devez gérer la précision
   • Vous devez gérer les flags hh h l ll j z
   Gestion de conversions plus délicates : eE, fF, gG, aA, n.
   • Gestion de flags plus delicats : *, $, L, ’ .
   • Gestion de flags non existants : %b pour afficher en binaire, %r pour afficher une
   chaine avec des caractères non imprimables, %k pour afficher une date à un format
   ISO quelconque, etc.
   • Gestion de modifieurs pour gérer les couleurs, les fd ou des choses fun comme ça :)
   printf("Le fichier {cyan}%s{eoc} contient : {red}%s{eoc}", filename, str) ;
   */




/*
 *Vous devez fournir un Makefile qui compilera une libftprintf.a. Cette lib sera linké
 à notre main de test pour vous donner votre résultat.
 */


#include "../incl/ft_printf.h"
/*
char	*ft_strsjoin(size_t n, ...)
{
	len total

	malloc

	cpy
	return (*s)
}
*/
int		main(int ac, char **av)
{
	int x = 5;
	float y = 0.35;
	double z = 0.987654;
	
	printf("여보세요%d", x);
	ft_putchar('\t');
//	ft_printf("%%i        |%x|\n", 1);
	ft_putchar('\n');

	z = 0;
	y =0;
	return (0);
}
