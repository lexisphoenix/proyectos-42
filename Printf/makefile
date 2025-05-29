# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anieto-m <anieto-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 14:53:20 by anieto-m          #+#    #+#              #
#    Updated: 2025/05/29 14:53:52 by anieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable final
NAME = programa

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Carpetas
LIBFT_DIR = ./libft
PRINTF_DIR = ./ft_printf

# Archivos
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_OBJS = $(PRINTF_DIR)/ft_printf.o \
			  $(PRINTF_DIR)/ft_putchar.o \
			  $(PRINTF_DIR)/ft_putstr.o \
			  $(PRINTF_DIR)/ft_putnbr.o \
			  $(PRINTF_DIR)/ft_putunsigned.o \
			  $(PRINTF_DIR)/ft_puthex.o \
			  $(PRINTF_DIR)/ft_putptr.o

MAIN = main.c
MAIN_OBJ = $(MAIN:.c=.o)

# Regla por defecto
all: $(NAME)

# Compilar programa final
$(NAME): $(MAIN_OBJ) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(PRINTF_OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compilar libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Limpiar objetos
clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(MAIN_OBJ) $(PRINTF_OBJS)

# Limpiar todo
fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

# Recompilar desde cero
re: fclean all

