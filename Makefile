# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 23:42:00 by matcardo          #+#    #+#              #
#    Updated: 2023/11/11 02:12:53 by thabeck-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= main.c								\
			init_map_functions.c					\
			init_player_and_bg_functions.c			\
			init_texture_functions.c				\
			hooks.c									\
			move_player.c							\
			print_screen_temp.c						\
			validation/check_args.c					\
			validation/check_args_utils.c			\
			validation/ftex_utils.c					\
			validation/map_validation.c				\
			validation/map_validation_utils.c		\
			validation/map_walls_validation.c		\
			validation/map_walls_validation_utils.c	\
			validation/parameter_validation_1.c		\
			validation/parameter_validation_2.c		\
			validation/parameter_utils.c			\
			validation/trim_map.c					\
			validation/validation_utils.c			\

OBJS		= ${SRCS:%.c=%.o}
OBJS_DIR	= objs/

RM			= rm -fr
CC			= gcc
FLAGS		= -Wall -Wextra -Werror

MLX			= ./libraries/minilibx-linux/libmlx.a
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
		@$(CC) $(FLAGS) $(addprefix $(OBJS_DIR),$(OBJS)) $(LIBFT) -L./libraries/minilibx-linux $(MLX) $(MLX_FLAGS) -o $(NAME)
		@printf "$(GR)cub3D is Ready!$(RC)\n"

#lembrar de criar os subdiretorios quando houver
$(OBJS_DIR):
	@mkdir $(OBJS_DIR) objs/validation/
	
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
		make -C ./libraries/minilibx-linux
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
		@make clean -C ./libraries/minilibx-linux
		@$(RM) $(OBJS_DIR) $(LEAKS_FILE) $(NAME)
		@printf "$(RE)Cub3D object files and executable removed!$(RC)\n"

re:			fclean all

# rebonus:	fclean bonus

.PHONY:		bonus all clean fclean re rebonus
