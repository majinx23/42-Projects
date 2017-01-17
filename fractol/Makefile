# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/15 23:54:02 by angavrel          #+#    #+#              #
#    Updated: 2017/01/17 16:11:52 by angavrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_PATH = srcs
OBJ_PATH = obj
INC_PATH = incl
LIBFT_PATH = libft

#SRC = main.c \
	  fractal_build.c \
	  hook.c \
	  key_hook.c \

SRC := $(shell ls -1 srcs)

LIBFT = -L $(LIBFT_PATH) -lft -lm

MINILIBX = -lmlx -framework OpenGl -framework AppKit

FLAGS = -Wall -Werror -Wextra

OBJ = $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))

INC = -I $(INC_PATH) -I $(LIBFT_PATH)/includes

all: lib $(NAME)

lib:
	#@make -C $(LIBFT_PATH)

$(NAME) : $(OBJ)
	@clang $(FLAGS) -o $(NAME) $(LIBFT) $(MINILIBX) $^
	@echo "\n\033[36;1m"$@ "program created\033[0m"
	@printf '\033[32;1m~~~~~~~~~~~~~~~~~~~~~~~~\n\033[0m'

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@clang $(FLAGS) $(INC) -o $@ -c $<
	@printf '\033[32;1m~~~~~~\033[0m'

clean:
	@echo "\033[31m.o files supressed\033[0m"
	@rm -rf $(OBJ)
	@make -C libft/ clean
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@echo "\033[31mProgram deleted\033[0m"
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all

norme:
	@norminette src/$(SRC)
	@norminette $(INC_PATH)/*.h

.PHONY: all lib clean fclean re norme
