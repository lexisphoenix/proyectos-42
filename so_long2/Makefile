
# CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -Ift_printf -Iminilibx/linux -DASSETS_DIR=\"assets\"
# CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -Ift_printf -Iminilibx/sierra
# MLX = -Lminilibx -lmlx -framework OpenGL -framework AppKit
# Compilador y flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Ilibft -Ift_printf -Iminilibx/linux -DASSETS_DIR=\"assets\"

# Nombre del ejecutable
NAME    = so_long

# Archivos fuente y objetos
SRCS    = src/main.c src/game.c src/map_parser.c get_next_line.c get_next_line_utils.c
OBJS    = $(SRCS:.c=.o)

# Librerías
LIBFT   = libft/libft.a
PRINTF  = ft_printf/libftprintf.a
MLX     = -Lminilibx/linux -lmlx -lXext -lX11 -lm
# MLX     = -Lminilibx/sierra -lmlx -framework OpenGL -framework AppKit

# Regla por defecto
all: $(NAME)

# Link final
$(NAME): $(OBJS) $(PRINTF) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(LIBFT) $(MLX_LIB) -lXext -lX11 -lm -o $(NAME)

# Cómo compilar los .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Sub-makes para libft y ft_printf
$(LIBFT):
	make -C libft

$(PRINTF):
	make -C ft_printf

clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C ft_printf clean
	make -C minilibx/linux clean
	
fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C ft_printf fclean
	rm -f minilibx/linux/libmlx.a

re: fclean all

.PHONY: all clean fclean re

# -Lminilibx/sierra -lmlx -framework OpenGL -framework AppKit
# MLX_DIR = minilibx/sierra
