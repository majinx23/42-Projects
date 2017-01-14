/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/14 23:51:49 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** fcntl to use O_RDONLY, math for formulacs, nlx.h to trace pixel and window
** colors to use custom colors and keycode handle buttons and clicks' events.
*/

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libmlx/mlx.h"
# include "colors.h"
# include "keycode_mac.h"


# define TITLE "FDF"

/*
** PI is equal to PI * 2^24 or << 24
*/

# define PI 31.41927

/*
** macros used for still inputs
*/

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK (1L << 0)
# define KEYRELEASEMASK (1L << 1)

/*
** more awesome colors
*/

# define PINK 0xcc00cc
# define BLACK 0x000000
# define MARINE_BLUE 0x000099
# define PONEY_PINK 0xffccff
# define CRIMSON_RED 0x990033
# define NICE_BLUE 0x6666ff
# define DARK_TEAL 0x33cccc
# define GREY 0xd3d3d3
# define BROWN 0x996633

/*
** using t_xy.x and t_xy.y instead of x and y for index.
*/

typedef struct	s_argb
{
	float		a;
	float		r;
	float		g;
	float		b;
}				t_argb;

typedef struct	s_argb2
{
	t_argb		x;
	t_argb		y;
}				t_argb2;

typedef struct	s_hsl
{
	float		h;
	float		s;
	float		l;
}				t_hsl;

typedef struct	s_hsb
{
	t_hsl		a;
	t_hsl		i;
}				t_hsb;

typedef struct	s_h
{
	float		max;
	float		min;
	float		d;
}				t_h;

typedef struct	s_uixy
{
	unsigned	x;
	unsigned	y;
}				t_uixy;

typedef struct	s_xy
{
	long	x;
	long	y;
}				t_xy;

typedef struct s_fxy
{
	float	x;
	float	y;
}				t_fxy;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vector;

typedef struct	s_fxyzw
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_fxyzw;

typedef struct s_xyz
{
	int		x;
	int		y;
	int		z;
}				t_xyz;


/*
** points are stored using this structure in convert_2_to_3d
*/
typedef struct	s_index
{
	short	x;
	short	y;
}				t_index;


typedef struct	s_uabcd
{
	unsigned	a;
	unsigned	b;
	unsigned	c;
	unsigned	d;
}				t_uabcd;

/*
** *s is map parsed as a string and *c a save from each point's color.
*/

typedef struct	s_3d
{
	t_index		max;
	float		depth;
	t_vector	offs;
	t_vector	scaling;
	t_fxy		center;
	float		z;
	float		v;
	t_vector	**m; //stores orginial input from file (z coords)
	t_vector	**mm; //modified 3d coords
	t_fxy		**n;
	char		*s;
	int			**c;
	void		*mlx;
	void		*w;
	int			*img;
	t_index		dimension;
	short		slope;
	char		*data_address;
	int			bpp;
	int			line_size;
	int			endian;
	t_xy		colors;
	float		**matrix;
	float		**matrix_tmp;
	short		z_max;
	short		z_min;
	short		season;
	t_argb		l;
	t_vector	angle;
	short		display;
}				t_3d;

/*
** parsing.c ~ parsing functions
*/

short			check_validity(char *s);
int				get_depth_and_colors(t_3d *d);
float			vector_len(int x, int y, int z);

/*
** formula.c ~ formulas, coordinates calculation and variables initialization
*/

float			get_3d_y(t_vector a, float depth);
float			get_3d_x(t_vector a);
int				convert_3_to_2d(t_3d *d);
void			init_variables(t_3d *d);
short			width(t_3d *d);
short			height(t_3d *d);

/*
** fdf.c ~ tracing lines algorythmes and listening to user input
*/

int				fdf(t_3d *d);
void			put_pixel_in_img(t_3d *d, t_fxy a, t_argb color);
void			draw(t_3d *d);
void			lines_draw(t_3d *d, t_fxy a, t_fxy b, t_uixy c);
void			create_image(t_3d *d);
int				user_input(int keycode, t_3d *d);

/*
** color.c ~ gradient colors functions
*/

void			color_map(t_3d *d);
t_argb2			gradient(unsigned a, unsigned b, int pixel);

/*
** matrix rotations
*/

float			**identity_matrix(void);
float			**matrix_rotation(float angle, char axis);
float			**matrix_scaling(t_vector scaling);
float			**matrix_translation(t_vector offset);
void			apply_matrix(t_3d *d);
t_vector		apply_matrix_to_point(float **m, t_vector v, t_fxy center);
float			**factor_matrix(float **a, float **b);
void			rotate(t_3d *d, char axis, char direction);

/*
** matrix2.c ~ vectors translation and rotation
*/

t_3d			*rotate_point(t_3d *d, t_xy i);

/*
** functions handling memory
*/
int				malloc_map(t_3d *d);
void			free_all(t_3d *d);
void			free_matrix(float **m);

#endif
