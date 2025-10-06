# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/20 21:39:13 by anieto-m          #+#    #+#              #
#    Updated: 2025/09/18 12:48:58 by anieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME		= libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDES)
AR			= ar rcs
RM			= rm -f

SRCS_DIR	= src/
OBJS_DIR	= obj/
INCLUDES	= .

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #

DEF_COLOR = \033[0;39m
GRAY      = \033[0;90m
RED       = \033[0;91m
GREEN     = \033[0;92m
YELLOW    = \033[0;93m
BLUE      = \033[0;94m
CYAN      = \033[0;96m

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

FTIS_DIR = ft_is/
FTIS     = ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint

FTMEM_DIR = ft_mem/
FTMEM    = ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset

FTPUT_DIR = ft_put/
FTPUT    = ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTTO_DIR = ft_to/
FTTO    = ft_atoi ft_itoa ft_uitoa ft_tolower ft_toupper

FTSTR_DIR = ft_str/
FTSTR   = ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
		  ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
		  ft_strnstr ft_strrchr ft_strtrim ft_substr

FTLST_DIR = ft_lst/
FTLST   = ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
		  ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

SRC_FILES = \
	$(addprefix $(FTIS_DIR),$(FTIS)) \
	$(addprefix $(FTMEM_DIR),$(FTMEM)) \
	$(addprefix $(FTPUT_DIR),$(FTPUT)) \
	$(addprefix $(FTTO_DIR),$(FTTO)) \
	$(addprefix $(FTSTR_DIR),$(FTSTR)) \
	$(addprefix $(FTLST_DIR),$(FTLST))

SRCS = $(addprefix $(SRCS_DIR),$(addsuffix .c,$(SRC_FILES)))
OBJS = $(addprefix $(OBJS_DIR),$(addsuffix .o,$(SRC_FILES)))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rf $(OBJS_DIR)
	@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) -f $(NAME)
	@echo "$(CYAN)libft library cleaned!$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt libft!$(DEF_COLOR)"

norm:
	@norminette $(SRCS) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm
