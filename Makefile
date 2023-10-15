# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 23:42:00 by matcardo          #+#    #+#              #
#    Updated: 2023/10/14 18:23:37 by matcardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= main.c			\
			check_args.c		\
			init_functions_1.c	\
			init_functions_2.c	\
			hooks.c				\
			move_player.c		\
			print_screen_temp.c	\

OBJS		= ${SRCS:%.c=%.o}
OBJS_DIR	= objs/

RM			= rm -fr
CC			= gcc
FLAGS		= -Wall -Wextra -Werror

MLX			= ./minilibx-linux/libmlx.a
MLX_FLAGS	=  -lm -lmlx -lXext -lX11
LIBFT		= ./libraries/libft/libft.a

LEAKS 		= valgrind
LEAKS_FILE	= valgrind-out.txt
LF 			= --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=$(LEAKS_FILE) \

GR				= \033[32;1m
RE				= \033[31;1m
CY				= \033[36;1m
RC				= \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS_DIR) $(addprefix $(OBJS_DIR),$(OBJS))
		@printf "\r$(CY)Generating cub3D executable...$(RC)\n"
		@$(CC) $(FLAGS) $(addprefix $(OBJS_DIR),$(OBJS)) $(LIBFT) -L./minilibx-linux $(MLX) $(MLX_FLAGS) -o $(NAME)
		@printf "$(GR)cub3D is Ready!$(RC)\n"

#lembrar de criar os subdiretorios quando houver
$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	
objs/%.o:	src/%.c ./inc/cub3D.h
#		@printf "\r$(CY)Generating object$(RC)\n"
		@$(CC) $(FLAGS) -c $< -o $@
#		@printf "$(GR)Object is ready!$(RC)\n"

$(LIBFT):
		@printf "$(CY)Generating libft...$(RC)\n"
		@make bonus -C ./libraries/libft
		@printf "$(GR)libft ready!$(RC)\n"

$(MLX):
		@printf "$(CY)Generating minilibx...$(RC)\n"
		make -C ./minilibx-linux
		@printf "$(GR)minilibx ready!$(RC)\n"

# descomenta se tiver algo do bonus	ou excluir
# bonus: $(NAME)

leaks:		$(NAME)
		$(LEAKS) $(LF) ./$(NAME)

norm:
	norminette ${SRCS}

clean:
		@make clean -C ./libraries/libft
		@$(RM) $(OBJS_DIR) $(LEAKS_FILE)
		@printf "$(RE)Cub3D object files removed!$(RC)\n"

fclean:	
		@make fclean -C ./libraries/libft
		@make clean -C ./minilibx-linux
		@$(RM) $(OBJS_DIR) $(LEAKS_FILE) $(NAME)
		@printf "$(RE)Cub3D object files and executable removed!$(RC)\n"

re:			fclean all

# rebonus:	fclean bonus

.PHONY:		bonus all clean fclean re rebonus
