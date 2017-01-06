/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:02:07 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/06 18:24:34 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 ** get the gradiant color increase
 */
float	gradient(unsigned a, unsigned b, int pixel)
{
	t_rgb		x;
	t_rgb		y;

	x.b = a % 0x100;
	y.b = a % 0x100;
	y.b = (y.b - x.b) / pixel;
	x.g = 0;
	y.g = 0;
	x.r = 0;
	y.r = 0;
	if (a >= 0x100)
		x.g = ((a % 0x10000) - x.b);
	if (b >= 256)
		y.g = (b % 0x10000) - y.b;
	y.g = (y.g - x.g) / pixel;
	if (a >= 0x10000)
		x.r = a - x.g;
	if (b >= 0x10000)
		y.r = b - y.g;
	y.r = (y.r - x.r) / pixel;
	y.r = y.r * 0x10000 + y.g * 0x100 + y.b;
	return (y.r);
}

/*
unsigned	hsl_to_hslint(t_hsl hsl, unsigned rgb)
{
	return (((unsigned int)(hsl.h * 0xff) << (0 * 8)) |
		((unsigned int)(hsl.s * 0xff) << (1 * 8)) |
		((unsigned int)(hsl.l * 0xff) << (2 * 8)) |
		(((rgb >> (3 * 8)) & 0xff) << (3 * 8)));
}
*/


t_hsl	rgb_to_hsl(unsigned rgb)  // Alpha value is simply passed through
{
	t_rgb	c;
	t_h		h;
	t_hsl	hsl;

	c.r = (rgb >> (0 * 8)) & 0xff,
	c.g = (rgb >> (1 * 8)) & 0xff,
	c.b = (rgb >> (2 * 8)) & 0xff;
	c.r /= 0xff;
	c.g /= 0xff;
	c.b /= 0xff;

	h.max = fmax(fmax(c.r, c.g), c.b);
	h.min = fmin(fmin(c.r, c.g), c.b);
	hsl.h = 0;
	hsl.s = 0;
	hsl.l = (h.max + h.min) / 2;
	if (h.max != h.min)
	{
		h.d = h.max - h.min;
		hsl.s = hsl.l > 0.5 ? h.d / (2 - h.max - h.min) : h.d / (h.max + h.min);
		if (h.max == c.r)
			hsl.h = (c.g - c.b) / h.d + (c.g < c.b ? 6 : 0);
		else if (h.max == c.g)
			hsl.h = (c.b - c.r) / h.d + 2;
		else if (h.max == c.b)
			hsl.h = (c.r - c.g) / h.d + 4;
		hsl.h /= 6;
	}
	//printf("%f hue : ", hsl.h);
	//printf("%f saturation : ", hsl.s);
	//printf("%f light : ", hsl.l);
	return (hsl);
}

static  float hue_to_rgb(float p, float q, float t)
{
	if (t < 0)
		t += 1;
	else if (t > 1)
		t -= 1;
	if (t < 1/6)
		return (p + (q - p) * 6 * t);
	if (t < 1/2)
		return (q);
	if (t < 2/3)
		return (p + (q - p) * (2/3 - t) * 6);
	return (p);
}


unsigned	hsl_to_rgb(t_hsl h)
{
	t_rgb	c;
	float	q;
	float	p;

	if (!h.s)
		c.r = c.g = c.b = h.l; // achromatic
	else
	{
		q = h.l < 0.5 ? h.l * (1 + h.s) : h.l * (1 - h.s) + h.s;
		printf("q = %f\n", q);
		p = 2 * h.l - q;
		printf("p = %f\n", p);
		c.r = 0xff * hue_to_rgb(p, q, h.h + 1/3);
		c.g = 0xff * hue_to_rgb(p, q, h.h);
		c.b = 0xff * hue_to_rgb(p, q, h.h - 1/3);
	}
	return ((unsigned)(c.r * 0x10000 + c.g * 0x100 + c.b));
}


t_hsb		get_gradient(unsigned rgb, unsigned rgb2, unsigned pixel)
{
	t_hsb		hsb;
	t_hsl		b;

	hsb.a = rgb_to_hsl(rgb);
	b = rgb_to_hsl(rgb2);
	hsb.i.h = (b.h - hsb.a.h) / pixel;
	hsb.i.s = (b.s - hsb.a.s) / pixel;
	hsb.i.l = (b.l - hsb.a.l) / pixel;
	return (hsb);
}
