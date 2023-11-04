# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/18 20:01:18 by vrichese          #+#    #+#              #
#    Updated: 2019/10/03 18:41:58 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						= OpenGL

SOURCE_DIR					= source
LIBS_DIR					= libs/
INCLUDE_DIR					= include

GLEW						= $(LIBS_DIR)libGLEW.2.1.0.dylib
GLFW						= $(LIBS_DIR)libglfw.3.3.dylib
DEVIL						= $(LIBS_DIR)libIL.dylib
OPENGL						= -framework OpenGL

FILES						= $(addprefix $(SOURCE_DIR)/, test.cpp)

OBJ							= ${FILES:%.cpp=%.o}

#CFLAGS						= -Wall -Werror -Wextra

CC							= g++

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(GLEW) $(GLFW) $(DEVIL) $(OPENGL) $^ -o $@

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(CC) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
