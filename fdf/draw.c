/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 14:17:05 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/06 16:59:14 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		user_input(int keycode, t_3d *d)
{
	//printf("ok%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx, d->w);
		exit(0);
		return (0);
	}
	if (keycode == 69 && d->zoom < 300)
	{
		d->zoom *= 1.25;
		fdf(d);
	}
	if (keycode == 78 && d->zoom > 1.25)
	{
		d->zoom *= 0.80;
		fdf(d);
	}
	if (keycode == 123)
	{
		d->offs.x -= d->zoom;
		fdf(d);
	}
	if (keycode == 124)
	{
		d->offs.x += d->zoom;
		fdf(d);
	}
	if (keycode == 125)
	{
		d->offs.y += d->zoom;
		fdf(d);
	}
	if (keycode == 126)
	{
		d->offs.y -= d->zoom;
		fdf(d);
	}
	return (1);
}

/*
 ** create a new image
 */
void	create_image(t_3d *d)
{
	d->img ? mlx_destroy_image(d->mlx, d->img) : 0;
	mlx_clear_window(d->mlx, d->w);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->data_address = mlx_get_data_addr(d->img, &(d->bpp),
			&(d->line_size), &(d->endian));
}

/*
 ** Puts exactly one pixel in the image
 ** As d->c[y][x] is the color expressed as integer, we take the address
 ** of d->data_address and then cast it as (int *) before dereferencing to
 ** save color value inside.
 */
void	put_pixel_in_image(t_3d *d, int x, int y, unsigned color)
{
	if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
		*(int *)&d->data_address[(x * d->bpp / 8) +
			(y * d->line_size)] = color;
}

/*
 ** draw line inside the image using bits

 void	vector2(t_3d *d, int ix, int iy, int color)
 {
 unsigned		l;
 unsigned long	x;
 unsigned long	y;
 int				dx;
 int				dy;

 x = (long)(d->n[iy][ix].x * 512 << 9) + 256; // maybe remove cast in long later
 y = (long)(d->n[iy][ix].y * 512 << 9) + 256;
 dx = (d->n[iy][ix + 1].x - d->n[iy][ix].x) * 512;
 dy = (d->n[iy][ix + 1].y - d->n[iy][ix].y) * 512;
 l = 0;
 while (l < 512)
 {
 printf("x = d->p[i->y][i->x].x: %lu   x << 9 + 255 : %lu   x >> 9 : %lu\n", d->n[iy][ix].x * 512, x, (x >> 9));
 mlx_pixel_put(d->mlx, d->w, 100 + (x >> 9), 100 + (y >> 9), color);
 x += dx;
 y += dy;
 ++l;
 }
 }
 */


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


/*
unsigned	hsl_to_rgb(t_3dunsigned hsl)
{
	t_hsl	hsl;
	t_rgb	c;
	
	hsl.h = ;
	hsl.s =;
	hsl.l =;

	if(s == 0)
		c.r = c.g = c.b = l; // achromatic
	else{
			function hue2rgb(p, q, t){
				if(t < 0) t += 1;
				if(t > 1) t -= 1;
				if(t < 1/6) return p + (q - p) * 6 * t;
				if(t < 1/2) return q;
				if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
				return p;
			}

			var q = l < 0.5 ? l * (1 + s) : l + s - l * s;
			var p = 2 * l - q;
			r = hue2rgb(p, q, h + 1/3);
			g = hue2rgb(p, q, h);
			b = hue2rgb(p, q, h - 1/3);
		}
		return (c.r * 0xff, c.g * 0xff, c.b * 0xff);
	}
}

*/
unsigned		get_gradient(unsigned rgb, unsigned rgb2, unsigned pixel)
{
	unsigned	hsl_unsigned;
	unsigned	hsl_unsigned2;
	t_hsl		hsl;
	t_hsl		hsl2;

	hsl = rgb_to_hsl(rgb);
	hsl_unsigned = hsl_to_hslint(hsl, rgb);
	hsl2 = rgb_to_hsl(rgb2);
	hsl_unsigned2 = hsl_to_hslint(hsl2, rgb2);
	return ((hsl_unsigned2 - hsl_unsigned) / pixel);
}
/*
 ** draw lines between points (no bits)
 */
void	lines_draw(t_3d *d, t_fxy a, t_fxy b, t_uixy c)
{
	t_fxy		dif;
	t_fxy		i;
	int			pixel;
	float		gradient_color;
	float		color;

	//printf("a.x : %lf  b.x : %lf  a.y: %lf  b.y: %lf\n", a.x, b.x, a.y, b.y);//
	ft_putnbr(b.x);
	dif.x = fabs(b.x - a.x);
	dif.y = fabs(b.y - a.y);
	//printf("dif x : %lf dif y: %lf\n", dif.x, dif.y);//
	pixel = (dif.x > dif.y) ? dif.x : dif.y;
	!pixel ? pixel = 1 : 0;
	i.x = dif.x / pixel * (a.x < b.x ? 1 : -1);
	i.y = dif.y / pixel * (a.y < b.y ? 1 : -1);
	//printf("pixels: %i\n", pixel);//
	//gradient_color = gradient(0xff /*c.x*/, 0xff00/*c.y*/, pixel);
	gradient_color = get_gradient(0xff, 0xffff, pixel);
	//printf("rgb > hsl : %f\n", gradient_color);
	color = hsl_to_hslint(rgb_to_hsl(0xff), 0xff);//c.x;
	c.x = 0;
	while (pixel--)
	{
		//printf("draw pixel(%lf, %lf)\n", a.x, a.y);//
		//mlx_pixel_put(d->mlx, d->w, round(a.x), round(a.y), NICE_BLUE);
		put_pixel_in_image(d, round(a.x), round(a.y), round(color));
		a.x += i.x;
		a.y += i.y;
		color += gradient_color;
	}
}
void	draw(t_3d *d)
{
	t_xy	i;
	t_uixy	color;

	i.y = -1;
	while (++i.y < d->y)
	{
		i.x = -1;
		while (++i.x < d->x)
		{
			color.x = d->c[i.y][i.x];
			if (i.x < d->x - 1)
			{
				color.y = d->c[i.y][i.x + 1];
				lines_draw(d, d->n[i.y][i.x], d->n[i.y][i.x + 1], color);
			}
			if (i.y < d->y - 1)
			{
				color.y = d->c[i.y + 1][i.x];
				lines_draw(d, d->n[i.y][i.x], d->n[i.y + 1][i.x], color);
			}
		}
	}
}

int		fdf(t_3d *d)
{
	if (!convert_3_to_2d(d))
		return (ft_error("Conversion to isometric 3d failed"));
	//d->mlx = mlx_init();
	//d->w = mlx_new_window(d->mlx, WIDTH, HEIGHT, TITLE);
	create_image(d);
	draw(d);
	mlx_put_image_to_window(d->mlx, d->w, d->img, 0, 0);
	mlx_string_put(d->mlx, d->w, 10, 10, 0x33ffaa, "Click to display commands");
	mlx_hook(d->w, KEYPRESS, KEYPRESSMASK, user_input, d);
	//mlx_key_hook(d->w,user_input, d);
	mlx_loop(d->mlx); // pixels' display is only at this point
	return (0);
}
