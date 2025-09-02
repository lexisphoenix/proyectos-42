NAME    = so_long
SRC     = main.c map_parser.c game.c get_next_line.c get_next_line_utils.c
OBJ     = $(SRC:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -D BUFFER_SIZE=42 -Iminilibx/sierra
LDFLAGS = -Lminilibx/sierra -lmlx -framework OpenGL -framework AppKit

MLX_DIR = minilibx/sierra
MLX     = $(MLX_DIR)/libmlx.a
ASSETS_DIR ?= assets
CFLAGS += -DASSETS_DIR=\"$(ASSETS_DIR)\"

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

run: $(NAME)
	./$(NAME) map.ber

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all run clean fclean re
