/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsb2rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:09:48 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/01 15:41:48 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include "libft.h"

t_rgb	ft_hsb2rgb(t_hsb hsb)
{
	t_rgb		rgb;
	t_vector	i;

	i.w = (int)(hsb.h / 60);
	i.w = (hsb.h / 60) - i.w;
	i.x = 0xff * (hsb.b * (1 - hsb.s));
	i.y = 0xff * (hsb.b * (1 - i.w * hsb.s));
	i.z = 0xff * (hsb.b * (1 - (1 - i.w) * hsb.s));
	hsb.b *= 0xff;
	hsb.h = (int)((hsb.h) / 60);
	if (hsb.h == 0)
		rgb = (t_rgb) {.r = hsb.b, .g = i.z, .b = i.x};
	else if (hsb.h == 1)
		rgb = (t_rgb) {.r = i.y, .g = hsb.b, .b = i.x};
	else if (hsb.h == 2)
		rgb = (t_rgb) {.r = i.x, .g = hsb.b, .b = i.z};
	else if (hsb.h == 3)
		rgb = (t_rgb) {.r = i.x, .g = i.y, hsb.b};
	else if (hsb.h == 4)
		rgb = (t_rgb) {.r = i.z, .g = i.x, hsb.b};
	else if (hsb.h == 5)
		rgb = (t_rgb) {.r = hsb.b, .g = i.x, .b = i.y};
	else
		rgb = (t_rgb) {.r = 0, .g = 0, .b = 0};
	return (rgb);
}
