.PHONY: all clean fclean re

NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	parser.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

debug:		CFLAGS	+= -fsanitize=address -g
debug:		all

$(NAME) :${OBJS} | tools
		${CC} -L ./mlx/ -L ./libft42/ -lft -lmlx -framework OpenGL -framework AppKit  -o ${NAME} ${OBJS}

tools:
	make -C ./libft42/
	make -C ./mlx/
clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME} 

re: fclean all