# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 19:19:12 by angavrel          #+#    #+#              #
#    Updated: 2017/01/19 23:07:43 by angavrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = fdf

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = libft

DIR_S = srcs

DIR_O = objs

DIR_MLX = libmlx

HEADERS = incl

SRC_NAME = main.c \
		   ft_parsing.c \
		   ft_formula.c \
		   ft_draw.c \
		   ft_color.c \
		   ft_matrix_operations.c \
		   ft_matrix_transformations.c \
		   ft_memory_handler.c \
		   ft_settings.c \
		   ft_hook.c \

SRCS = $(addprefix $(DIR_S)/,$(SRC_NAME))

OBJS = $(addprefix $(DIR_O)/,$(SRC_NAME:.c=.o))

all: temp $(NAME)

$(NAME): $(OBJS)
#	@make -C $(LIBFT)
#	@make -C $(DIR_MLX)
	@$(CC) $(FLAGS) -L $(LIBFT) -lft -o $@ $^ -framework OpenGL -framework AppKit -L $(DIR_MLX) -lmlx
	@echo "\033[0;32m$(NAME)'s program created.\033[0m"

temp:
	@mkdir -p objs

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

clean:
	@rm -f $(OBJS)
#	@make clean -C $(LIBFT)
#	@make clean -C $(DIR_MLX)
	@rm -rf $(DIR_O)
	@echo "\033[0;32m$(NAME)'s .o files deleted.\033[0m"

fclean: clean
	@rm -f $(NAME)
#	@make fclean -C $(LIBFT)
	@echo "\033[0;32m$(NAME) Project fully cleaned.\033[0m"

re: fclean all

.PHONY: all, temp, clean, fclean, re
