/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/09 17:54:55 by angavrel         ###   ########.fr       */
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
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "colors.h"
# include "keycode_mac.h"

# define TITLE "FDF"
//# define WIDTH (8 * 1.4 * (d->x + d->y))
//# define HEIGHT 1.2 * (d->x + d->x) //(d->margin_bot - d->margin_top) / 4
# define DY (d->p[i.y][i.x + 1].y - d->p[i.y][i.x].y)
# define DX (d->p[i.y][i.x + 1].x - d->p[i.y][i.x].x)


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

typedef struct	s_rgb
{
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct	s_rgb2
{
	t_rgb		x;
	t_rgb		y;
}				t_rgb2;

typedef struct	s_rgbxy
{
	t_rgb		x;
	t_rgb		y;
}				t_rgbxy;

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

typedef struct	s_fxyz
{
	float	x;
	float	y;
	float	z;
}				t_fxyz;

typedef struct s_xyz
{
	long	x;
	long	y;
	long	z;
}				t_xyz;


typedef struct	s_matrix
{
	float	n[4][4];
}				t_matrix;

/*
** points are stored using this structure in convert_2_to_3d
*/
typedef struct	s_index
{
	short	x;
	short	y;
}				t_index;

/*
** *s is map parsed as a string and *c a save from each point's color.
*/

typedef struct	s_3d
{
	short		y;
	short		x;
	float		z;
	long		depth;
	float		v;
	float		phi;//
	float		theta;//
	int			**m; //stores orginial input from file (z coords)
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
	float		zoom;
	t_xy		offs;
	t_xy		colors;
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
float			get_3d_y(int x, int y, int z, t_3d *d);
float			get_3d_x(int x, int y);
int				convert_3_to_2d(t_3d *d);
void			init_variables(t_3d *d);
short			width(t_3d *d);
short			height(t_3d *d);

/*
** fdf.c ~ tracing lines algorythmes and listening to user input
*/
int				fdf(t_3d *d);
void			put_pixel_in_img(t_3d *d, int a, int b, unsigned color);
//void			vector2(t_3d *d, int ix, int iy, int color);
void			draw(t_3d *d);
void			lines_draw(t_3d *d, t_fxy a, t_fxy b, t_uixy c);
void			create_image(t_3d *d);
int				user_input(int keycode, t_3d *d);

/*
** ?.c ~ vectors translation and rotation
*/
t_3d			*rotate_point(t_3d *d, t_xy i);

/*
** color.c ~ gradient colors functions
*/
t_rgb2			gradient(unsigned a, unsigned b, int pixel);
//unsigned		hsl_to_hslint(t_hsl hsl, unsigned rgb);
t_hsl			rgb_to_hsl(unsigned rgb);
unsigned		hsl_to_rgb(t_hsl h);
t_hsb			get_gradient(unsigned rgb, unsigned rgb2, unsigned pixel);

/*
** matrix rotations
*/
float		**identity_matrix(void);
float		**matrix_rotation_x(t_3d *d, float x);
float		**matrix_rotation_y(t_3d *d, float y);
float		**matrix_rotation_z(t_3d *d, float z);

#endif
