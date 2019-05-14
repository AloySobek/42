# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 18:23:00 by vrichese          #+#    #+#              #
#    Updated: 2019/05/11 18:52:52 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ./libft/ft_atoi.c ./ft_printf.c ./ft_uputnbrbase.c ./ft_putnbrbase.c ./ft_putcharbase.c ./ft_putstrbase.c ./libft/ft_putchar.c ./libft/ft_putstr.c ./libft/ft_isspace.c ./libft/ft_strnew.c ./libft/ft_strlen.c ./libft/ft_memset.c ./chars_handler.c ./digits_handler.c ./putstruni.c ./doubles_handler.c ./ft_putfloat.c

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
