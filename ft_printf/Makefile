NAME = libftprintf.a

SRC_DIRS := .

SRCS := ft_printf.c \
 define_var.c \
 print_char.c \
 print_string.c \
 print_decimal.c \
 print_unsigned_d.c \
 print_low_hex.c \
 print_up_hex.c \
 print_percent.c \
 print_ptr.c \


OBJECTS := $(SRCS:.c=.o)

CC := gcc

CFLAGS += -Wall -Wextra -Werror -g3

RM := rm -f

.o: .c
	$(CC) $(CFLAGS) $(OBJECTS) -c $< -o -I

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

all: $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

