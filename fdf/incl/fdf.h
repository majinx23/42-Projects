/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/19 21:30:11 by angavrel         ###   ########.fr       */
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

# define TITLE					"FDF"
# define HELP_COLOR				WHITE
# define HEIGHT					1400
# define WIDTH					2000

/*
** macros used for still inputs
*/

# define KEYPRESS				2
# define KEYRELEASE				3
# define KEYPRESSMASK			(1L << 0)
# define KEYRELEASEMASK			(1L << 1)

/*
** more awesome colors
*/

# define PINK					0xcc00cc
# define BLACK					0x000000
# define MARINE_BLUE			0x000099
# define CRIMSON_RED			0x990033
# define NICE_BLUE				0x6666ff
# define DARK_TEAL				0x33cccc
# define GREY					0xd3d3d3
# define BROWN					0x996633
# define SLIGHTLY_TRANSPARENT	0x77000000

/*
** a is alpha(transparency) r = red g = green b = blue
*/

typedef struct	s_argb
{
	float		a;
	float		r;
	float		g;
	float		b;
}				t_argb;

/*
** color gradient function
*/
typedef struct	s_argb2
{
	t_argb		x;
	t_argb		y;
}				t_argb2;

typedef struct	s_uixy
{
	unsigned	x;
	unsigned	y;
}				t_uixy;

typedef struct	s_fxy
{
	float		x;
	float		y;
}				t_fxy;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector;

/*
** points are stored using this structure in convert_2_to_3d
*/

typedef struct	s_index
{
	int			x;
	int			y;
}				t_index;


/*
** *s is map parsed as a string and *c a save from each point's color.
*/
typedef struct	s_3d
{
	char		*s;

	void		*mlx;
	void		*w;
	int			*img;
	char		*data_address;
	int			bpp;
	int			line_size;
	int			endian;

	t_index		max;
	float		depth;
	t_vector	angle;
	t_vector	offs;
	t_vector	scaling;
	t_vector	center;
	t_index		dimension;

	t_vector	**m;
	t_vector	**mm;
	int			**c;
	t_uixy		colors;
	float		**matrix;
	float		**matrix_tmp;
	short		z_max;
	short		z_min;
	short		season;
	t_argb		l;
	short		help_display;
}				t_3d;

/*
** parsing.c ~ parsing functions
*/

short			check_validity(char *s);
int				get_depth_and_colors(t_3d *d);

/*
** formula.c ~ formulas, coordinates calculation and variables initialization
*/

float			get_3d_y(t_vector a);
float			get_3d_x(t_vector a);
float			vector_len(t_vector v);

/*
**
*/

void			init_variables(t_3d *d);

/*
** fdf.c & hook.c ~ tracing lines algorythmes and listening to user input
*/

int				fdf(t_3d *d);
void			put_pixel_in_img(t_3d *d, t_vector a, t_argb color);
void			ft_draw(t_3d *d);
void			lines_draw(t_3d *d, t_vector a, t_vector b, t_uixy c);
void			ft_create_image(t_3d *d);
int				user_input(int keycode, t_3d *d);
void			ft_settings(t_3d *d);
/*
** color.c ~ gradient colors functions
*/

void			color_map(t_3d *d);
t_argb2			gradient(unsigned a, unsigned b, int pixel);

/*
** ft_matrix_transformations.c ~ matrix rotations
*/

float			**identity_matrix(int n, short iden);
float			**matrix_rotation(float angle, char axis);
float			**matrix_scaling(t_vector scaling);
float			**matrix_translation(t_vector offset);
void			matrix_magnitude(t_3d *d, float depth);
void			rotate(t_3d *d, char axis, char direction);
float			**ft_matrix_global_rotation(t_vector angle);

/*
** ft_matrix_operations.c ~ vectors translation and rotation
*/

void			apply_matrix(t_3d *d);
t_vector		apply_matrix_to_point(float **m, t_vector v, t_vector center);
float			**ft_factor_matrix_free(float **a, float **b, char free);
float			**sum_matrix(float **a, float **b);
void			ft_print_matrix(float **m);

/*
** memory_manager.c ~ functions handling memory
*/

int				malloc_map(t_3d *d);
void			free_all(t_3d *d);
void			free_matrix(float **m);

#endif
