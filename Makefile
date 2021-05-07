.PHONY: all clean fclean re

NAME = cub3D

CC = gcc

INCLUDES =	-I ./includes/ -I ./libft42/ -I ./mlx/

LIBS_ADD =	-L ./mlx/ -L ./libft42/ -lft -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror -O3 ${INCLUDES}

SRCS = 	$(addprefix ./src/,\
				cast_tools.c caster.c event.c exit.c main.c map_validation.c minimap.c param_proc.c \
				pars_map.c pars_param.c parsing.c raycasting.c rendering.c screen.c sprite_tools.c sprites.c\
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
		rm -f Screenshot.bmp
		make -C ./libft42/ clean
		make -C ./mlx/ clean

fclean:	clean
		rm -f ${NAME} 
		make -C ./libft42/ fclean
		make -C ./mlx/ fclean

re: fclean all