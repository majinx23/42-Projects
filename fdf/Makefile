### COMPILATION ###
C      = gcc
FLAGS  = -Wall -Wextra -Werror

### EXECUTABLE ###
NAME   = fdf

### INCLUDES ###
LIBFT  = libft
OBJ_PATH  = objs
HEADER = incl
SRC_PATH  = srcs
MLX_PATH = libmlx
LIBFTMATH_PATH = libftmath

### SOURCES ###
SOURCES = main.c \
		  ft_parsing.c \
		  ft_formula.c \
		  ft_draw.c \
		  ft_color.c \
		  ft_matrix_operations.c \
		  ft_matrix_transformations.c \
		  ft_memory_handler.c \
		  ft_settings.c \
		  ft_hook.c \

### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

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

all: tmp $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Creating lib files$(CYAN)"
	@make -C $(LIBFT)
	@make -C $(LIBFTMATH_PATH)
	@make -C $(MLX_PATH)
	@$(CC) $(FLAGS) -L $(LIBFT) -lft -o $@ $^ -framework OpenGL -framework AppKit -L $(MLX_PATH) -lmlx -L $(LIBFTMATH_PATH) -lftmath
	@echo "$(GREEN)Project successfully compiled"

tmp:
	@mkdir -p objs

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADER) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFTMATH_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFTMATH_PATH)

re: fclean
	@$(MAKE) all -j

.PHONY: temporary, re, clean
