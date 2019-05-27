NAME = libftprintf.a

SRCDIR = srcs

SRC =     $(addprefix $(SRCDIR)/, ft_printf.c char_handlers.c constructor.c\
                addit_func.c decimal_handlers.c double_handlers.c \
                pars_string.c print_any_char.c print_any_string.c \
                print_double.c print_expo_double.c print_sig_dig.c print_uns_dig.c\
        	ft_atoi.c ft_isspace.c ft_strlen.c ft_bzero.c ft_strcmp.c long_arithmetic.c)

OBJ = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I./includes $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
