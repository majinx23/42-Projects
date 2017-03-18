# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/28 18:36:22 by angavrel          #+#    #+#              #
#    Updated: 2017/03/18 19:11:05 by angavrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = angavrel.filler

FLAGS = -Wall -Werror -Wextra
INC = -I ./incl/

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = libft/

SRCS_NAME =	main.c \
			parse.c \
			valid_positions.c \
			solve.c \
			break_through.c \
			reach_borders.c \
			check_min.c \
			debug.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

$(NAME): $(OBJ)
#	make -C $(LIBFT_PATH)
	gcc $(FLAGS) $(OBJ) $(INC) -L $(LIBFT_PATH) -lft -framework OpenGL -framework AppKit -lmlx -o $(NAME)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	gcc -c $(FLAGS) $< $(INC) -o $@

clean:
#	make -C $(LIBFT_PATH) fclean
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
