/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 23:58:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/18 11:12:39 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <mlx.h>
# include "../libft/libft.h"
# include "keycode_mac.h"
# include "colors.h"
# include <stdio.h>//

# define TITLE				"Fractol"
# define HEIGHT				800
# define WIDTH				900
# define HELP_COLOR			0xffffff


enum	e_fractal{MANDELBROT, JULIA, PHOENIX, BARNSLEY};

/*
** stands for complex number
*/
typedef struct		s_cnb
{
	double			real;
	double			imag;
}					t_cnb;

typedef struct		s_index
{
	double			x;
	double			y;
}					t_index;

typedef struct		s_max
{
	double			x;
	double			y;
}						t_max;

typedef struct		s_i
{
	int				i;
	int				max;

}					t_i;
/*
** i is pixel nb and f is current iteration
*/

typedef struct			s_3d
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	enum e_fractal	fractal;
	t_index			i;
	t_i				f;
	t_max			max;

	double			zoom;
	t_index			offset;
	int				iter_coef;

	t_cnb			c_point;
	
	t_cnb			c;
	short			fern;
	unsigned		fern_motion;

	int				julia_static;
	t_cnb			julia;
	int				color;
	int				menu;
	short			rng;
	short			a;
}						t_3d;

/*     
** Parsing and variable t_3d initialization
*/

int						usage();
int						init_variables(t_3d *d);
void					init_img(t_3d *d);
void					put_pixel_in_img(t_3d *d, int x, int y, int color);
void					settings_background(t_3d *d);


/*
** Fractol program
*/

void					init_fractal(t_3d *d, char *name);
unsigned int			create_color(int r, int g, int b);
void					fractol(t_3d *d);
void					get_fractal(t_3d *d);
unsigned				color_pixel(t_3d *d, t_cnb *z, int i);
unsigned int			linear_interpolation(double hue);

/*
** fractol initialization
*/

void					init_julia_set(t_3d *d);
void					init_phoenix(t_3d *d);
void					init_julia(t_3d *d);
void					init_mandelbrot(t_3d *d);

void					init_barnsley(t_3d *d);
/*
**  -0.506667 0.520000       0.403333  0.273333
*/

void					mandelbrot(t_3d *d, t_cnb z, t_cnb c);
void					julia(t_3d *d, t_cnb c);
void					phoenix(t_3d *d, t_cnb z, t_cnb c);
void					barnsley(t_3d *d);
void					barnsley_fern_algo(t_i *i, t_cnb c, float rng, t_3d *d);
/*
** Hook to check for user input
*/

int						motion_hook(int x, int y, t_3d *d);
int						key_hook(int keycode, t_3d *d);
//void					apply_scaling(t_3d *d, int keycode);
int						mouse_scaling_hook(int button, int x, int y, t_3d *d);

#endif
