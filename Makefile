# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 10:53:07 by ojoubout          #+#    #+#              #
#    Updated: 2019/11/23 22:10:50 by ojoubout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3d

SRC = srcs/main.c srcs/draw.c srcs/shapes.c srcs/free.c srcs/move.c srcs/ray.c \
srcs/texture.c srcs/read.c srcs/maze.c srcs/misc.c srcs/bitmap.c
SRC += gnl/get_next_line.c
# SRC += libft/*.c

OBJ = $(SRC:.c=.o)
MLX= -framework OpenGL -framework AppKit -lmlx
FLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C libft all bonus
	@gcc $(FLAGS) $(MLX) $(SRC) libft/libft.a -Iincludes -o $(NAME)

	# @gcc $(FLAGS) -g -framework OpenGL -framework AppKit $(SRC) -Iincludes -lmlx -o $(NAME)

clean:
	@make -C libft fclean
	@rm -rf *.bmp


fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: fclean clean all bonus re
