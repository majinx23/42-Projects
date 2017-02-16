# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 19:19:12 by angavrel          #+#    #+#              #
#    Updated: 2017/02/16 19:07:18 by angavrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME = fdf

### COMPILATION ###
CC      = gcc
FLAGS   = -Wall -Wextra -Werror
MAKE    = make -C

### INCLUDES ###
HEADERS = incl/
LIBFT_PATH = libft/
#LIBMATH_PATH = libmath/
SOURCE_PATH = srcs/
OBJS_PATH = objs/
MLX_PATH = libmlx/

### SOURCES ###
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

SRCS = $(addprefix $(SOURCE_PATH),$(SRC_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(SRC_NAME:.c=.o))

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###
all: objs lib $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling objects files into $(NAME)...$(NOC)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS_PATH) -I $(LIBFT_PATH) -I $(HEADERS) -L $(LIBFT_PATH) -lft
	@$(CC) $(FLAGS) -I $(OBJS) $@ $<
	@make -C $(LIBMATH_PATH)
	@echo "$(GREEN)$(NAME)'s program created.$(NOC)"

lib:
	@make -C $(LIBFT_PATH)

mlx: $(OBJS)
	@echo "$(GREEN)Compiling objects files into $(NAME)...$(NOC)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) -I $(LIBFT_PATH) -I $(HEADERS) -L $(LIBFT_PATH) -lft  -framework OpenGL -framework AppKit -L $(MLX_PATH) -lmlx
#	@make -C $(LIBMATH_PATH)
	@make -C $(MLX_PATH)
	@echo "$(GREEN)$(NAME)'s program created.$(NOC)"

objs:
	@mkdir -p objs

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]"


clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(LIBMATH_PATH)
	@make clean -C $(MLX_PATH)
	@rmdir $(OBJS_PATH) 2> /dev/null || true
	@echo "$(GREEN)$(NAME)'s .o files deleted.$(NOC)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(LIBMATH_PATH)
	@echo "$(GREEB)$(NAME) Project fully cleaned.$(NOC)"

re: fclean all

.PHONY: all, objs, lib, mlx, clean, fclean, re
