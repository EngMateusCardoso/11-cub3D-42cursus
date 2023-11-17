# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 23:42:00 by matcardo          #+#    #+#              #
#    Updated: 2023/11/17 20:12:31 by thabeck-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= main.c								\
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
			init/init_map_functions.c				\
			init/init_player_and_bg_functions.c		\
			init/init_texture_functions.c			\
			print_screen/print_screen.c				\
			print_screen/raycaster.c				\
			print_screen/horizontal_hit.c			\
			print_screen/vertical_hit.c				\
			print_screen/draw_walls.c				\
			hooks/hooks.c							\
			hooks/move_player.c						\

SRCS_BONUS	= main_bonus.c									\
			validation/check_args_bonus.c					\
			validation/check_args_utils_bonus.c				\
			validation/ftex_utils_bonus.c					\
			validation/map_validation_bonus.c				\
			validation/map_validation_utils_bonus.c			\
			validation/map_walls_validation_bonus.c			\
			validation/map_walls_validation_utils_bonus.c	\
			validation/parameter_validation_1_bonus.c		\
			validation/parameter_validation_2_bonus.c		\
			validation/parameter_utils_bonus.c				\
			validation/trim_map_bonus.c						\
			validation/validation_utils_bonus.c				\
			init/init_map_functions_bonus.c					\
			init/init_player_and_bg_functions_bonus.c		\
			init/init_texture_functions_bonus.c				\
			print_screen/print_screen_bonus.c				\
			print_screen/raycaster_bonus.c					\
			print_screen/horizontal_hit_bonus.c				\
			print_screen/vertical_hit_bonus.c				\
			print_screen/draw_walls_bonus.c					\
			print_screen/minimap_bonus.c					\
			hooks/hooks_bonus.c								\
			hooks/mouse_hooks_bonus.c						\
			hooks/move_player_bonus.c						\

OBJS		= ${SRCS:%.c=%.o}
OBJS_BONUS	= ${SRCS_BONUS:%.c=%.o}
OBJS_DIR	= objs/
OBJS_DIR_B	= objs_bonus/

RM			= rm -fr
CC			= gcc
FLAGS		= -Wall -Wextra -Werror

MLX			= /usr/local/lib/libmlx.a
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
	@$(CC) $(FLAGS) $(addprefix $(OBJS_DIR),$(OBJS)) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GR)cub3D is Ready!$(RC)\n"

bonus: $(LIBFT) $(MLX) $(OBJS_DIR_B) $(addprefix $(OBJS_DIR_B),$(OBJS_BONUS))
	@printf "\r$(CY)Generating cub3D executable...$(RC)\n"
	@$(CC) $(FLAGS) $(addprefix $(OBJS_DIR_B),$(OBJS_BONUS)) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GR)cub3D is Ready!$(RC)\n"

#lembrar de criar os subdiretorios quando houver
$(OBJS_DIR):
	@mkdir $(OBJS_DIR) objs/validation/ objs/init/ objs/print_screen/ objs/hooks/

$(OBJS_DIR_B):
	@mkdir $(OBJS_DIR_B) objs_bonus/validation/ objs_bonus/init/ objs_bonus/print_screen/ objs_bonus/hooks/
	
objs/%.o:	src/%.c ./inc/cub3D.h
	@$(CC) $(FLAGS) -c $< -o $@

objs_bonus/%.o:	src_bonus/%.c ./inc_bonus/cub3D_bonus.h
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@make bonus -C ./libraries/libft

leaks:		$(NAME)
		$(LEAKS) $(LF) ./$(NAME)

norm:
	norminette ${SRCS} ${SRCS_BONUS}

clean:
	@make clean -C ./libraries/libft
	@$(RM) $(OBJS_DIR) $(OBJS_DIR_B) $(LEAKS_FILE)
	@printf "$(RE)Cub3D object files removed!$(RC)\n"

fclean:	
	@make fclean -C ./libraries/libft
	@$(RM) $(OBJS_DIR) $(OBJS_DIR_B) $(LEAKS_FILE) $(NAME)
	@printf "$(RE)Cub3D object files and executable removed!$(RC)\n"

re:			fclean all

rebonus:	fclean bonus

.PHONY:		bonus all clean fclean re rebonus
