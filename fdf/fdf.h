/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 07:14:02 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/27 19:17:24 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define WIDTH = 400
# define HEIGHT = 600

/*
** My Colors
*/
# define BLUE = 0x0000ff
# define RED = 0xcc0000
# define GREEN = 0x00cc00
# define TEAL = 0x00ffff
# define PURPLE = 0x9900cc
# define PINK = 0xcc00cc
# define ORANGE = 0xff6600
# define WHITE = 0xeeffff
# define GOLD = 0xffd700
# define BLACK = 0x000000
# define MARINE_BLUE = 0x000099
# define LIME = 0x00ff00
# define SKY_BLUE = 0x33ccff
# define NIGHT_BLUE = 0x006699
# define PONEY_PINK = 0xffccff
# define CRIMSON_RED = 0x990033
# define NICE_BLUE = 0x6666ff
# define DARK_TEAL = 0x33cccc
# define GREY = 0xd3d3d3
# define BROWN = 0x996633

double		vector_len(double x, double y, double z);

typedef struct	s_3d
{
	double		y;
	double		x;
	double		z;
	double		w;
	double		phi;
	double		theta;
	double		**m;
}				t_3d;

int				check_RGB_validity(char *s);
int				check_digit_validity(char *s, unsigned i);
int				check_validity(char *s);
int				get_x_y(t_3d *d, char *s);
void			get_map_dimension(t_3d *d, char *s);

#endif
