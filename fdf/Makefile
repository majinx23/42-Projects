# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 19:19:12 by angavrel          #+#    #+#              #
#    Updated: 2016/12/29 21:49:39 by angavrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -Llibft

LDLIBS = -lft

CPPFLAGS = -I.

MLX =-L ./minilibx_macos/ -framework OPENGL -framework AppKit -lmlx

SRC_NAME = main.c \
		   formula.c \
		   parsing.c \
		   tracing.c
		  # $(NAME).c

OBJ_NAME = $(SRC_NAME:.c=.o)

HEAD = $(NAME).h

all: $(NAME)

$(NAME): $(OBJ_NAME)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(LDFLAGS) $(MLX) $(LDLIBS) -I ./ $^ -o $@
	@echo "\033[0;32m$(NAME)'s program created.\033[0m"

$(OBJ)%.o: $(SRC)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ_NAME)
	@rm -f $(OBJ)
	@echo "\033[0;32m$(NAME)'s .o files deleted.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C ./Libft fclean
	@echo "\033[0;32m$(NAME) Project fully cleaned.\033[0m"

re: fclean all

.PHONY: all clean fclean re
