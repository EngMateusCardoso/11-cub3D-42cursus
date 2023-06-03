# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 23:42:00 by matcardo          #+#    #+#              #
#    Updated: 2023/06/03 18:01:33 by matcardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= ./src/main.c

OBJS		= ${SRCS:.c=.o}

RM			= rm -f
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
MLX			= ./minilibx-linux/libmlx.a
MLX_FLAGS	= -lXext -lX11 -lm
LIBFT		= ./libraries/libft/libft.a

LEAKS 		= valgrind
LEAKS_FILE	= valgrind-out.txt
LF 			= --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=$(LEAKS_FILE) \
			./cub3D

all: $(NAME)

.c.o:
		$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

# depois fazer para o mac
$(MLX):
		make -C ./minilibx-linux
$(LIBFT):
		make -C ./libraries/libft

$(NAME): $(OBJS) $(MLX) $(LIBFT)
		$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)

bonus: $(NAME)

leaks: 
	$(LEAKS) $(LF)

norm:
	norminette ${SRCS}

clean:
		make -C ./libraries/libft clean
		$(RM) $(OBJS)

fclean:	clean
		make -C ./minilibx-linux clean
		make -C ./libraries/libft fclean
		$(RM) $(NAME)

re:			fclean all

rebonus:	fclean bonus

.PHONY:		bonus all clean fclean re rebonus
