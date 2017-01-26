/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 23:58:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/26 17:21:47 by angavrel         ###   ########.fr       */
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


enum	e_fractal{MANDELBROT, JULIA, PHOENIX, BARNSLEY, KOCH};

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

typedef	struct		s_rgb2
{
	t_rgb			x;
	t_rgb			y;
}					t_rgb2;

/*
** colored vector
*/
typedef	struct		s_cv
{
	double		x;
	double		y;
	unsigned	color;
}					t_cv;



typedef struct	s_image
{
	void		*mlx;
	void		*win;
	int			*image;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_image;


/*
** i is pixel nb and f is current iteration
*/


typedef struct			s_3d
{
	t_image			img;
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
	short			koch_size;
	short			koch_order;
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
void					ft_blackscreen(t_3d *d);

/*
** Fractol program
*/

void					fractol(t_3d *d);
void					get_fractal(t_3d *d);
void					ft_draw_line(t_3d *d, t_cv a, t_cv b);
/*
** fractals initialization
*/

void					init_fractal(t_3d *d, char *name);
void					init_julia_set(t_3d *d);
void					init_phoenix(t_3d *d);
void					init_julia(t_3d *d);
void					init_mandelbrot(t_3d *d);
void					init_barnsley(t_3d *d);
void					init_koch(t_3d *d);

/*
** Fractals algorytms
*/

void					mandelbrot(t_3d *d, t_cnb z, t_cnb c);
void					julia(t_3d *d, t_cnb c);
void					phoenix(t_3d *d, t_cnb z, t_cnb c);
void					barnsley_fern_algo(t_i *i, t_cnb c, float rng, t_3d *d);
void					koch_snowflake_algo(t_3d *d);

/*
** color functions
*/

unsigned				color_pixel(t_3d *d, int a);
unsigned				ft_rainbow_gradient(double x);
t_rgb2					ft_gradient(unsigned a, unsigned b, int pixel);

/*
** Hook to check for user input
*/

int						motion_hook(int x, int y, t_3d *d);
int						key_hook(int keycode, t_3d *d);
int						mouse_scaling_hook(int button, int x, int y, t_3d *d);

#endif
