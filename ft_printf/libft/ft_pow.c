/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 19:38:26 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/27 20:07:31 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_pow(long n, int pow)
{
	return (pow ? n * ft_pow(n, pow - 1) : 1);
}
