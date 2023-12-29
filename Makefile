# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 20:38:47 by kevso             #+#    #+#              #
#    Updated: 2023/12/29 17:27:46 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS := -Llibft -lft -lreadline
INC_DIR := -Iinc -Ilibft/inc

# Directories
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := libft

# Files /!\ ENLEVER WILDCARD ET METTRE LES SOURCES 1 PAR 1 AVANT LE PUSH FINAL /!\ 
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Main executable
NAME := minishell

.PHONY: all clean fclean re

all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all
