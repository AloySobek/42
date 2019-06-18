NAME	=	libftprintf.a

SRCDIR	=	srcs

LIBDIR	=	lib_func

SRC		=	$(addprefix $(SRCDIR)/, ft_printf.c char_handlers.c constructor.c chooser_betw_f_e.c \
			addit_func.c decimal_handlers.c double_handlers.c parse_string.c print_char.c \
			print_double.c print_hexadouble.c print_integer.c scientific_record_funcs.c \
			long_arithmetic.c long_arithmetic2.c long_arithmetic3.c)

LIB		=	$(addprefix $(LIBDIR)/, ft_atoi.c ft_bzero.c ft_isspace.c ft_memcpy.c ft_strcmp.c ft_strlen.c)

OBJ		=	${SRC:.c=.o} ${LIB:.c=.o} 

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c
$(LIBDIR)/%.o: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) -I./includes -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
