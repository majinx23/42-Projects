/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/03 19:43:29 by angavrel         ###   ########.fr       */
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
# define WIDTH 900//(51 * (1.2 * (d->x + d->y)))
# define HEIGHT 600//(600 + 1.2 * 512 * (d->margin_bot - d->margin_top))
# define DY (d->p[i.y][i.x + 1].y - d->p[i.y][i.x].y)
# define DX (d->p[i.y][i.x + 1].x - d->p[i.y][i.x].x)
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

typedef struct s_xyz
{
	long	x;
	long	y;
	long	z;
}				t_xyz;

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
	int			margin_top;
	int			margin_bot;
	int			offs;
	short		slope;
	char		*data_address;
	int			bpp;
	int			line_size;
	int			endian;
	int			zoom;
	int			x_tr;
	int			y_tr;
}				t_3d;

/*
** check_validity checks that map is valid and parse color.
** get_map_dimension malloc x y z into **m
*/
short			check_validity(char *s);
int				get_depth_and_colors(t_3d *d);
float			vector_len(int x, int y, int z);
float			get_3d_y(int x, int y, int z);
float			get_3d_x(int x, int y);
int				convert_3_to_2d(t_3d *d);
int				put_pixels(t_3d *d);
void			put_pixel_in_image(t_3d *d, t_xy i);
//void			vector2(t_3d *d, int ix, int iy, int color);
void			draw(t_3d *d, t_fxy a, t_fxy b);
void			init_variables(t_3d *d);
void			create_image(t_3d *d);
void			destroy_image(t_3d *d);
void			close_window(t_3d *d);
t_3d			*rotate_point(t_3d *d, t_xy i);

#endif
