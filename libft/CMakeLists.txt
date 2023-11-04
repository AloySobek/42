cmake_minimum_required(VERSION 3.0.0)

project(libft VERSION 1.0)

set(GCC_COVERAGE_COMPILE_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "-03")

set(SOURCE
    ${PROJECT_SOURCE_DIR}/src/ft_atoi.c
    ${PROJECT_SOURCE_DIR}/src/ft_bzero.c
    ${PROJECT_SOURCE_DIR}/src/ft_isalnum.c
    ${PROJECT_SOURCE_DIR}/src/ft_isalpha.c
    ${PROJECT_SOURCE_DIR}/src/ft_isascii.c
    ${PROJECT_SOURCE_DIR}/src/ft_isblank.c
    ${PROJECT_SOURCE_DIR}/src/ft_iscntrl.c
    ${PROJECT_SOURCE_DIR}/src/ft_isdigit.c
    ${PROJECT_SOURCE_DIR}/src/ft_islower.c
    ${PROJECT_SOURCE_DIR}/src/ft_isprint.c
    ${PROJECT_SOURCE_DIR}/src/ft_isspace.c
    ${PROJECT_SOURCE_DIR}/src/ft_isupper.c
    ${PROJECT_SOURCE_DIR}/src/ft_itoa.c
    ${PROJECT_SOURCE_DIR}/src/ft_lstadd.c
    ${PROJECT_SOURCE_DIR}/src/ft_lstaddend.c
    ${PROJECT_SOURCE_DIR}/src/ft_lstdel.c
    ${PROJECT_SOURCE_DIR}/src/ft_lstdelone.c
    ${PROJECT_SOURCE_DIR}/src/ft_lstiter.c
    ${PROJECT_SOURCE_DIR}/src/ft_lstmap.c
    ${PROJECT_SOURCE_DIR}/src/ft_lstnew.c
    ${PROJECT_SOURCE_DIR}/src/ft_memalloc.c
    ${PROJECT_SOURCE_DIR}/src/ft_memccpy.c
    ${PROJECT_SOURCE_DIR}/src/ft_memchr.c
    ${PROJECT_SOURCE_DIR}/src/ft_memcmp.c
    ${PROJECT_SOURCE_DIR}/src/ft_memcpy.c
    ${PROJECT_SOURCE_DIR}/src/ft_memdel.c
    ${PROJECT_SOURCE_DIR}/src/ft_memmove.c
    ${PROJECT_SOURCE_DIR}/src/ft_memset.c
    ${PROJECT_SOURCE_DIR}/src/ft_nbrlen.c
    ${PROJECT_SOURCE_DIR}/src/ft_putchar.c
    ${PROJECT_SOURCE_DIR}/src/ft_putchar_fd.c
    ${PROJECT_SOURCE_DIR}/src/ft_putendl.c
    ${PROJECT_SOURCE_DIR}/src/ft_putendl_fd.c
    ${PROJECT_SOURCE_DIR}/src/ft_putnbr.c
    ${PROJECT_SOURCE_DIR}/src/ft_putnbr_fd.c
    ${PROJECT_SOURCE_DIR}/src/ft_putstr.c
    ${PROJECT_SOURCE_DIR}/src/ft_putstr_fd.c
    ${PROJECT_SOURCE_DIR}/src/ft_realloc.c
    ${PROJECT_SOURCE_DIR}/src/ft_strcat.c
    ${PROJECT_SOURCE_DIR}/src/ft_strchr.c
    ${PROJECT_SOURCE_DIR}/src/ft_strclen.c
    ${PROJECT_SOURCE_DIR}/src/ft_strclr.c
    ${PROJECT_SOURCE_DIR}/src/ft_strcmp.c
    ${PROJECT_SOURCE_DIR}/src/ft_strcpy.c
    ${PROJECT_SOURCE_DIR}/src/ft_strcrop.c
    ${PROJECT_SOURCE_DIR}/src/ft_strcut.c
    ${PROJECT_SOURCE_DIR}/src/ft_strdel.c
    ${PROJECT_SOURCE_DIR}/src/ft_strdup.c
    ${PROJECT_SOURCE_DIR}/src/ft_strequ.c
    ${PROJECT_SOURCE_DIR}/src/ft_striter.c
    ${PROJECT_SOURCE_DIR}/src/ft_striteri.c
    ${PROJECT_SOURCE_DIR}/src/ft_strjoin.c
    ${PROJECT_SOURCE_DIR}/src/ft_strlcat.c
    ${PROJECT_SOURCE_DIR}/src/ft_strlen.c
    ${PROJECT_SOURCE_DIR}/src/ft_strmap.c
    ${PROJECT_SOURCE_DIR}/src/ft_strmapi.c
    ${PROJECT_SOURCE_DIR}/src/ft_strncat.c
    ${PROJECT_SOURCE_DIR}/src/ft_strncmp.c
    ${PROJECT_SOURCE_DIR}/src/ft_strncpy.c
    ${PROJECT_SOURCE_DIR}/src/ft_strnequ.c
    ${PROJECT_SOURCE_DIR}/src/ft_strnew.c
    ${PROJECT_SOURCE_DIR}/src/ft_strnjoin.c
    ${PROJECT_SOURCE_DIR}/src/ft_strnlen.c
    ${PROJECT_SOURCE_DIR}/src/ft_strnstr.c
    ${PROJECT_SOURCE_DIR}/src/ft_strrchr.c
    ${PROJECT_SOURCE_DIR}/src/ft_strsplit.c
    ${PROJECT_SOURCE_DIR}/src/ft_strstr.c
    ${PROJECT_SOURCE_DIR}/src/ft_strsub.c
    ${PROJECT_SOURCE_DIR}/src/ft_strtrim.c
    ${PROJECT_SOURCE_DIR}/src/ft_tolower.c
    ${PROJECT_SOURCE_DIR}/src/ft_toupper.c)

add_library(${PROJECT_NAME} STATIC ${SOURCE})
