# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:30:22 by kvisouth          #+#    #+#              #
#    Updated: 2023/05/30 12:25:46 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c \
	src/lexer.c \
	src/executor.c \
	
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
