# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#              #
#    Updated: 2025/09/18 16:55:25 by anieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

CC      = cc
NAME    = so_long

# Detect OS and set appropriate flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address \
             -Iincludes -Ilibft -Ift_printf -Iminilibx/X11/minilibx -DASSETS_DIR=\"assets\"
    MLX_DIR = minilibx/X11/minilibx
    MLX_LIB = $(MLX_DIR)/libmlx.a
    MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else
    CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address \
             -Iincludes -Ilibft -Ift_printf -Iminilibx/sierra -DASSETS_DIR=\"assets\"
    MLX_DIR = minilibx/sierra
    MLX_LIB = $(MLX_DIR)/libmlx.a
    MLX     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# Archivos fuente
SRCS = src/main.c \
       src/map_parser.c \
       src/map_validation.c \
       src/map_pathfinding.c \
       src/game_render.c \
       src/game_animation.c \
       src/game_movement.c \
       src/game_hooks.c \
       src/game_init.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c
OBJS    = $(SRCS:.c=.o)

LIBFT   = libft/libft.a
PRINTF  = ft_printf/libftprintf.a

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