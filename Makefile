# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 23:42:00 by matcardo          #+#    #+#              #
#    Updated: 2023/06/07 02:17:42 by matcardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= main.c

OBJS		= ${SRCS:%.c=%.o}
OBJS_DIR	= objs/

RM			= rm -fr
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

GR				= \033[32;1m
RE				= \033[31;1m
CY				= \033[36;1m
RC				= \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(addprefix $(OBJS_DIR),$(OBJS))
		@printf "\r$(CY)Generating cub3D executable...$(RC)\n"
		@$(CC) $(FLAGS) $(addprefix $(OBJS_DIR),$(OBJS)) -o $(NAME) $(LIBFT) $(MLX) $(MLX_FLAGS)
		@printf "$(GR)cub3D is Ready!$(RC)\n"

#lembrar de criar os subdiretorios quando houver
$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	
objs/%.o:	src/%.c
		@printf "\r$(CY)Generating object "$@
		@$(CC) $(FLAGS) -c -o $@ $<

$(LIBFT):
		@printf "$(CY)Generating libft...$(RC)\n"
		@make bonus -C ./libraries/libft
		@printf "$(GR)libft ready!$(RC)"

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
		@$(RM) $(OBJS_DIR) $(LEAKS_FILE) $(NAME)
		@printf "$(RE)Cub3D object files and executable removed!$(RC)\n"

re:			fclean all

# rebonus:	fclean bonus

.PHONY:		bonus all clean fclean re rebonus
