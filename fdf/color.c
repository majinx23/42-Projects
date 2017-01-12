/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:02:07 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/12 23:47:43 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** stores the needed gradiant color increase in c.y and starting color in c.x
** on bitwise operators: a & 0xFF is equivalent to a % 256  as 0xFF = 255. 
** >> 8 is used to divide color by 2^8 = 256, removing blue, and then red.
** the more c.x.a is close to 0xff and the more it will be transparent.
*/

t_argb2				gradient(unsigned a, unsigned b, int pixel)
{
	t_argb2		c;

	c.x.b = a & 0xFF;
	c.y.b = b & 0xFF;
	c.y.b = (c.y.b - c.x.b) / pixel;
	c.x.g = a >> 8 & 0xFF;
	c.y.g = b >> 8 & 0xFF;
	c.y.g = (c.y.g - c.x.g) / pixel;
	c.x.r = a >> 16 & 0xFF;
	c.y.r = b >> 16 & 0xFF;
	c.y.r = (c.y.r - c.x.r) / pixel;
	c.x.a = a >> 24;
	c.y.a = b >> 24;
	c.y.a = (c.y.a - c.x.a) / pixel;
	return (c);
}

/*
** ssaw : 0 = spring, 1 = summer, 2 = autumn, 3 = winter.
** level : 0 lowest, 3 highest.
*/

static	unsigned	season(int ssaw, int level)
{
	unsigned season[4][4];

	season[0][0] = NICE_BLUE;
	season[0][1] = LAWN_GREEN;
	season[0][2] = BROWN;
	season[0][3] = WHITE;
	season[1][0] = CYAN;
	season[1][1] = NICE_BLUE;
	season[1][2] = RED;
	season[1][3] = WHITE;
	season[2][0] = GOLD;
	season[2][1] = RED;
	season[2][2] = GOLD;
	season[2][3] = WHITE;
	season[3][0] = CORAL;
	season[3][1] = SKY_BLUE;
	season[3][2] = NICE_BLUE;
	season[3][3] = WHITE;
	return (season[ssaw][level]);
}

/*
** Shiki no Uta ~ colors map using above function
*/

void	color_map(t_3d *d)
{
	t_index		i;
	float		range;

	range = d->z_max - d->z_min;
	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
			if (d->m[i.y][i.x].z - d->z_min < 0.25 * range)
				d->c[i.y][i.x] = season(d->season, 0);
			else if (d->m[i.y][i.x].z - d->z_min < 0.65 * range)
				d->c[i.y][i.x] = season(d->season, 1);
			else if (d->m[i.y][i.x].z - d->z_min < 0.85 * range)
				d->c[i.y][i.x] = season(d->season, 2);
			else
				d->c[i.y][i.x] = season(d->season, 3);
			++i.x;
		}
		++i.y;
	}
}

/*
unsigned	hsl_to_hslint(t_hsl hsl, unsigned rgb)
{
	return (((unsigned int)(hsl.h * 0xff) << (0 * 8)) |
		((unsigned int)(hsl.s * 0xff) << (1 * 8)) |
		((unsigned int)(hsl.l * 0xff) << (2 * 8)) |
		(((rgb >> (3 * 8)) & 0xff) << (3 * 8)));
}



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

*/
