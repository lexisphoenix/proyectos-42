# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 17:16:31 by anieto-m          #+#    #+#              #
#    Updated: 2025/05/15 19:55:29 by anieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile
NAME = libft.a
SRC = ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# -------- PRUEBAS --------

# Puedes cambiar el archivo de test aquí para probar otro
TEST_SRC = test/main_strchr_strrchr.c
TEST_OBJ = $(TEST_SRC:.c=.o)

test: fclean $(NAME)
	$(CC) $(CFLAGS) $(TEST_SRC) $(NAME) -o test_exec && ./test_exec

.PHONY: all clean fclean re test