/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/30 15:11:57 by angavrel         ###   ########.fr       */
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

# define WIDTH (200 + (d->x + d->y))
# define HEIGHT (200 + (d->margin_bot - d->margin_top))

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
	char		*s;
	int			**c;
	void		*mlx;
	void		*w;
	int			margin_top;
	int			margin_bot;
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
int				convert_2d_to_3d(t_3d *d);
int				put_pixels(t_3d *d);


#endif
