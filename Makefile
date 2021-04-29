.PHONY: all clean fclean re

NAME = cub3D

CC = gcc

INCLUDES =	-I ./includes/ -I ./libft42/ -I ./mlx/

LIBS_ADD =	-L ./mlx/ -L ./libft42/ -lft -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror -O3 ${INCLUDES}

SRCS = 	$(addprefix ./src/,\
				main.c parsing.c event.c raycasting.c rendering.c sprites.c screen.c minimap.c\
		)

OBJS = $(SRCS:.c=.o)

all: ${NAME}

debug:		CFLAGS	+= -fsanitize=address -g
debug:		all

$(NAME) :${OBJS} | tools
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS_ADD}

tools:
	make -C ./libft42/
	make -C ./mlx/

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME} 

re: fclean all