
# CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -Ift_printf -Iminilibx/linux -DASSETS_DIR=\"assets\"
# CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -Ift_printf -Iminilibx/sierra
# MLX = -Lminilibx -lmlx -framework OpenGL -framework AppKit
# Compilador y flags
# Compilador y flags

# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

CC      = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address \
         -Iincludes -Ilibft -Ift_printf -Iminilibx/linux -DASSETS_DIR=\"assets\"

NAME    = so_long

# Archivos fuente (automático: todos los .c de src/)
SRCS = $(wildcard src/*.c) \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c
OBJS    = $(SRCS:.c=.o)

LIBFT   = libft/libft.a
PRINTF  = ft_printf/libftprintf.a

MLX_DIR = minilibx/linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT) $(MLX_LIB)
	@echo "\033[1;32m[LINK]\033[0m $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(LIBFT) $(MLX) -o $(NAME)

%.o: %.c
	@echo "\033[1;34m[CC]\033[0m $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

$(PRINTF):
	@$(MAKE) -C ft_printf

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean
	@$(MAKE) -C ft_printf clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "\033[1;33m[INFO]\033[0m Objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C ft_printf fclean
	@rm -f $(MLX_LIB)
	@echo "\033[1;33m[INFO]\033[0m All cleaned"

re: fclean all

.PHONY: all clean fclean re
