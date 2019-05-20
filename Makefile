# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 18:23:00 by vrichese          #+#    #+#              #
#    Updated: 2019/05/20 15:16:56 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCDIR = srcs

SRC =     $(addprefix $(SRCDIR)/, ft_printf.c char_handlers.c constructor.c\
		decimal_handlers_addit.c decimal_handlers.c double_handlers.c \
		pars_string.c print_any_char.c print_any_string.c \
		print_double.c print_expo_double.c print_sig_dig.c print_uns_dig.c\
        ft_atoi.c ft_isspace.c ft_strlen.c\
        ft_memset.c ft_bzero.c)

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: $(SRCDIR)%.c
    
	@gcc -c $<

clean:
    
	@rm -f $(OBJ)

fclean: clean
    
	@rm -f $(NAME)

re: fclean all
