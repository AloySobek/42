cmake_minimum_required(VERSION 3.0.0)

project(ft VERSION 1.0 DESCRIPTION "C functions library")

set(GCC_COVERAGE_COMPILE_FLAGS "-O3")
set(GCC_COVERAGE_LINK_FLAGS "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE
	${PROJECT_SOURCE_DIR}/source/ft_atoi.c
	${PROJECT_SOURCE_DIR}/source/ft_bzero.c
	${PROJECT_SOURCE_DIR}/source/ft_isalnum.c
	${PROJECT_SOURCE_DIR}/source/ft_isalpha.c
	${PROJECT_SOURCE_DIR}/source/ft_isascii.c
	${PROJECT_SOURCE_DIR}/source/ft_isblank.c
	${PROJECT_SOURCE_DIR}/source/ft_iscntrl.c
	${PROJECT_SOURCE_DIR}/source/ft_isdigit.c
	${PROJECT_SOURCE_DIR}/source/ft_islower.c
	${PROJECT_SOURCE_DIR}/source/ft_isprint.c
	${PROJECT_SOURCE_DIR}/source/ft_isspace.c
	${PROJECT_SOURCE_DIR}/source/ft_isupper.c
	${PROJECT_SOURCE_DIR}/source/ft_itoa.c
	${PROJECT_SOURCE_DIR}/source/ft_lstadd.c
	${PROJECT_SOURCE_DIR}/source/ft_lstaddend.c
	${PROJECT_SOURCE_DIR}/source/ft_lstdel.c
	${PROJECT_SOURCE_DIR}/source/ft_lstdelone.c
	${PROJECT_SOURCE_DIR}/source/ft_lstiter.c
	${PROJECT_SOURCE_DIR}/source/ft_lstmap.c
	${PROJECT_SOURCE_DIR}/source/ft_lstnew.c
	${PROJECT_SOURCE_DIR}/source/ft_memalloc.c
	${PROJECT_SOURCE_DIR}/source/ft_memccpy.c
	${PROJECT_SOURCE_DIR}/source/ft_memchr.c
	${PROJECT_SOURCE_DIR}/source/ft_memcmp.c
	${PROJECT_SOURCE_DIR}/source/ft_memcpy.c
	${PROJECT_SOURCE_DIR}/source/ft_memdel.c
	${PROJECT_SOURCE_DIR}/source/ft_memmove.c
	${PROJECT_SOURCE_DIR}/source/ft_memset.c
	${PROJECT_SOURCE_DIR}/source/ft_nbrlen.c
	${PROJECT_SOURCE_DIR}/source/ft_putchar.c
	${PROJECT_SOURCE_DIR}/source/ft_putchar_fd.c
	${PROJECT_SOURCE_DIR}/source/ft_putendl.c
	${PROJECT_SOURCE_DIR}/source/ft_putendl_fd.c
	${PROJECT_SOURCE_DIR}/source/ft_putnbr.c
	${PROJECT_SOURCE_DIR}/source/ft_putnbr_fd.c
	${PROJECT_SOURCE_DIR}/source/ft_putstr.c
	${PROJECT_SOURCE_DIR}/source/ft_putstr_fd.c
	${PROJECT_SOURCE_DIR}/source/ft_realloc.c
	${PROJECT_SOURCE_DIR}/source/ft_strcat.c
	${PROJECT_SOURCE_DIR}/source/ft_strchr.c
	${PROJECT_SOURCE_DIR}/source/ft_strclen.c
	${PROJECT_SOURCE_DIR}/source/ft_strclr.c
	${PROJECT_SOURCE_DIR}/source/ft_strcmp.c
	${PROJECT_SOURCE_DIR}/source/ft_strcpy.c
	${PROJECT_SOURCE_DIR}/source/ft_strcrop.c
	${PROJECT_SOURCE_DIR}/source/ft_strcut.c
	${PROJECT_SOURCE_DIR}/source/ft_strdel.c
	${PROJECT_SOURCE_DIR}/source/ft_strdup.c
	${PROJECT_SOURCE_DIR}/source/ft_strequ.c
	${PROJECT_SOURCE_DIR}/source/ft_striter.c
	${PROJECT_SOURCE_DIR}/source/ft_striteri.c
	${PROJECT_SOURCE_DIR}/source/ft_strjoin.c
	${PROJECT_SOURCE_DIR}/source/ft_strlcat.c
	${PROJECT_SOURCE_DIR}/source/ft_strlen.c
	${PROJECT_SOURCE_DIR}/source/ft_strmap.c
	${PROJECT_SOURCE_DIR}/source/ft_strmapi.c
	${PROJECT_SOURCE_DIR}/source/ft_strncat.c
	${PROJECT_SOURCE_DIR}/source/ft_strncmp.c
	${PROJECT_SOURCE_DIR}/source/ft_strncpy.c
	${PROJECT_SOURCE_DIR}/source/ft_strnequ.c
	${PROJECT_SOURCE_DIR}/source/ft_strnew.c
	${PROJECT_SOURCE_DIR}/source/ft_strnjoin.c
	${PROJECT_SOURCE_DIR}/source/ft_strnlen.c
	${PROJECT_SOURCE_DIR}/source/ft_strnstr.c
	${PROJECT_SOURCE_DIR}/source/ft_strrchr.c
	${PROJECT_SOURCE_DIR}/source/ft_strsplit.c
	${PROJECT_SOURCE_DIR}/source/ft_strstr.c
	${PROJECT_SOURCE_DIR}/source/ft_strsub.c
	${PROJECT_SOURCE_DIR}/source/ft_strtrim.c
	${PROJECT_SOURCE_DIR}/source/ft_tolower.c
	${PROJECT_SOURCE_DIR}/source/ft_toupper.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})