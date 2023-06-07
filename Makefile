# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:30:22 by kvisouth          #+#    #+#              #
#    Updated: 2023/06/02 14:43:43 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c \
	src/lexer.c \
	src/parse_string.c \
	src/handle_quotes.c \
	src/executor.c \
	src/lexer_utils.c \
	src/print.c \
	src/redirection.c \
	src/builtins.c \
	src/builtin_echo.c \
	src/end.c \
	
OBJ = $(addprefix obj/, $(SRC:.c=.o))
HEADERS = minishell.h
CFLAGS = -Wall -Wextra -Werror -g3
CC = gcc


all: libft $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -Llibft -lft -lreadline

obj/%.o: %.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	@$(MAKE) -C libft

clean:
	@rm -rf obj
	@$(MAKE) -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft
