# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 18:23:00 by vrichese          #+#    #+#              #
#    Updated: 2019/05/15 15:40:28 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ./libft/ft_atoi.c ./ft_printf.c ./print_uns_dig.c ./print_sig_dig.c ./print_any_char.c ./print_any_string.c ./libft/ft_isspace.c ./char_handlers.c ./decimal_handlers.c ./double_handlers.c ./print_double.c ./print_expo_double.c ./pars_string.c ./decimal_handlers_addit.c ./constructor.c ./libft/ft_strlen.c 

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: srcs/%.c
	@gcc -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
