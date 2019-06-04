NAME = libftprintf.a

SRCDIR = srcs

SRC =     $(addprefix $(SRCDIR)/, ft_printf.c char_handlers.c constructor.c \
		  		addit_func.c decimal_handlers.c double_handlers.c \
				parse_string.c print_char.c print_double.c print_expo_double.c \
				print_integer.c ft_atoi.c ft_isspace.c ft_strlen.c \
				ft_bzero.c ft_strcmp.c ft_memcpy.c long_arithmetic.c)

OBJ = ${SRC:.c=.o}

CC = gcc

#CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I./includes -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
