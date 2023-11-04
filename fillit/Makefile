# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:27:59 by cnikia            #+#    #+#              #
#    Updated: 2019/04/29 19:45:38 by cnikia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS =  -Wall -Werror -Wextra 
SRC = main.c exit.c tetrimino_read.c coords.c extern_funct.c to_place.c
OPTIONS = -I./ -c -g
CHAHE = $(SRC:.c=.o)
LIB = ./libft/libft.a
all: $(NAME)

$(NAME): lib
	gcc $(FLAGS) $(OPTIONS) $(SRC)
	gcc -o $(NAME) -g $(CHAHE) $(LIB)
	
lib:
	make -C libft
clean:
	/bin/rm -f $(CHAHE)
	make -C libft clean
fclean: clean
	/bin/rm -f $(NAME)
	make -C libft fclean
re: fclean all
