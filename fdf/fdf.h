/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/28 20:23:59 by angavrel         ###   ########.fr       */
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

# define WIDTH 400
# define HEIGHT 600

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

double		vector_len(double x, double y, double z);


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
	float		y;
	float		x;
	float		z;
	float		w;
	float		phi;
	float		theta;
	float		**m;
	char		*s;
	int			**c;
}				t_3d;

/*
** check_validity checks that map is valid and parse color.
** get_map_dimension malloc x y z into **m
*/
unsigned		check_validity(t_3d *d, char *s);
int				get_map_dimension(t_3d *d);

#endif
