/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/30 21:20:19 by angavrel         ###   ########.fr       */
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

# define WIDTH (100 + 1.2 * (d->x + d->y))
# define HEIGHT (100 + 6 * (d->margin_bot - d->margin_top))
# define dy (d->p[i.y][i.x + 1].y - d->p[i.y][i.x].y)
# define dx (d->p[i.y][i.x + 1].x - d->p[i.y][i.x].x)
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
	unsigned	x;
	unsigned	y;
}				t_xy;


/*
** points are stored using this structure in convert_2_to_3d
*/
typedef struct	s_2p
{
	float		x;
	float		y;
}				t_2p;

/*
** *s is map parsed as a string and *c a save from each point's color.
*/

typedef struct	s_3d
{
	unsigned	y;
	unsigned	x;
	float		z;
	float		v;
	float		phi;
	float		theta;
	float		**m;
	float		**n;
	t_2p		**p;
	char		*s;
	int			**c;
	void		*mlx;
	void		*w;
	int			margin_top;
	int			margin_bot;
	int			offs;
	short		slope;
}				t_3d;

/*
** check_validity checks that map is valid and parse color.
** get_map_dimension malloc x y z into **m
*/
unsigned		check_validity(char *s);
int				get_depth_and_colors(t_3d *d);
float			vector_len(int x, int y, int z);
float			get_3d_y(int x, int y, int z);
float			get_3d_x(int x, int y);
int				convert_2_to_3d(t_3d *d);
int				put_pixels(t_3d *d);


#endif
