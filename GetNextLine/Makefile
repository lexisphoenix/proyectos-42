# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anieto-m <anieto-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 15:17:48 by anieto-m          #+#    #+#              #
#    Updated: 2025/05/29 15:17:52 by anieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl_test
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line.c get_next_line_utils.c main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

