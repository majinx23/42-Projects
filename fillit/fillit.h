/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:56:49 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 15:05:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define USAGE "usage: ./fillit source_file"
# define CHAR_EMPTY '.'
# define CHAR_FULL '#'
# define T_SIZE (T_WIDTH * T_HEIGHT)
# define T_WIDTH (4 + 1)
# define T_HEIGHT (4)
# define T_MAX 26
# define MAX_BUFFER_SIZE (T_SIZE + 1) * T_MAX

# include "./Libft/libft.h"
# include <fcntl.h>

typedef struct	s_pt
{
	short	x;
	short	y;
}				t_pt;

typedef struct	s_map
{
	short		**m;
	short		size;
	short		i;
	short		total;
}				t_map;

typedef struct	s_tetrimino
{
	t_pt	*pts;
	short	i;
	short	x;
	short	y;
}				t_tetrimino;

int				fillit(char *fd);
char			*read_file(char *av);
t_tetrimino		*check_validity(char *input, short num);
short			check_input_length(char *t, short num);
short			check_t_format(char **ts);
char			**t_split(char *s, short num);
short			check_full_char(char **ts);
short			check_pattern(char *t, short i, short *connections);
t_tetrimino		*set_tetriminos(char **ts, short num);
void			set_reference(char *t, t_pt *ref);
t_tetrimino		set_points(char *ts, t_pt ref);
void			display_usage(void);
void			display_error_message(void);
t_map			solve(t_tetrimino *ts, short size, short num);
short			get_first_size(short nb);
short			gen_map(t_map *m, short size, short num);
short			fill_map(t_map *m, t_tetrimino *ts);
short			place_t(t_map *m, t_tetrimino *ts);
short			update_map(t_map *m, t_tetrimino *ts);
void			increment_t_coords(t_tetrimino *ts, t_map *m);
void			remove_t(t_map *m, t_tetrimino *ts);
void			reset_map(t_map *m, t_tetrimino *ts);
void			reset_t_coords(t_tetrimino *ts);
char			**get_final_map(t_map *m, t_tetrimino *ts);
void			set_char(char **result, t_tetrimino *ts);
void			print_result(char **m, t_map *map);

#endif
