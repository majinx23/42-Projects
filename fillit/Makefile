# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 13:07:31 by jwalsh            #+#    #+#              #
#    Updated: 2016/11/25 15:48:24 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fillit

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -LLibft

LDLIBS = -lft

CPPFLAGS = -I.

SRC_NAME = main.c \
		   fillit.c \
		   read_file.c \
		   check.c \
		   t_split.c \
		   set_tetri.c \
		   map.c \
		   points.c \
		   solve.c \
		   print.c \
		   error.c 

OBJ_NAME = $(SRC_NAME:.c=.o)

HEAD = fillit.h

all: $(NAME)

$(NAME): $(OBJ_NAME)
	@make -C ./Libft
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -I ./ $^ -o $@

$(OBJ)%.o: $(SRC)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@-/bin/rm -f $(OBJ_NAME)
	@make -C ./Libft clean
	@echo "\033[0;32mFillit's .o files deleted\033[0m"

fclean: clean
	@-/bin/rm -f $(NAME)
	@make -C ./Libft fclean
	@echo "\033[0;32mFillit Project fully cleaned\033[0m"

re: fclean all

.PHONY: all clean fclean re
