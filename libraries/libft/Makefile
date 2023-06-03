# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 19:09:59 by thabeck-          #+#    #+#              #
#    Updated: 2023/02/26 13:25:16 by matcardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
GREEN		= \033[0;32m
RESET		= \033[0m
CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra
RM 			= rm -f
HDR			= libft.h
SRCS 		= ft_isalpha.c 			\
			ft_isdigit.c 			\
			ft_isalnum.c 			\
			ft_isascii.c 			\
			ft_isprint.c 			\
			ft_isdigit_sign.c 		\
			ft_isquote.c			\
			ft_strlen.c 			\
			ft_memset.c 			\
			ft_bzero.c 				\
			ft_memcpy.c 			\
			ft_memmove.c 			\
			ft_strlcpy.c 			\
			ft_strlcat.c 			\
			ft_toupper.c 			\
			ft_tolower.c 			\
			ft_strchr.c 			\
			ft_strrchr.c 			\
			ft_strncmp.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_strnstr.c			\
			ft_atoi.c 				\
			ft_strdup.c 			\
			ft_calloc.c 			\
			ft_substr.c				\
			ft_strjoin.c			\
			ft_strtrim.c			\
			ft_split.c				\
			ft_itoa.c				\
			ft_strmapi.c			\
			ft_striteri.c			\
			ft_putchar_fd.c			\
			ft_putstr_fd.c			\
			ft_putendl_fd.c			\
			ft_putnbr_fd.c			\
			ft_putstr_color_fd.c	\
			ft_straddchar.c			\
			ft_str_isnumeric.c		\
			ft_arrlen.c				\
			ft_swap.c				\
			ft_free_array.c			\
			ft_free_pointer.c		\


BONUS_SRCS  = ft_lstnew.c			\
			ft_lstadd_front.c  		\
			ft_lstsize.c 			\
			ft_lstlast.c			\
			ft_lstadd_back.c		\
			ft_lstdelone.c 			\
			ft_lstclear.c			\
			ft_lstiter.c			\
			ft_lstmap.c				\

OBJS 		= $(SRCS:.c=.o)
BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)

GR				= \033[32;1m
RE				= \033[31;1m
CY				= \033[36;1m
RC				= \033[0m

all:		$(NAME)

$(NAME): 	$(OBJS) $(HDR)
	@ ar -rcs $(NAME) $(OBJS)

bonus:		$(NAME) $(BONUS_OBJS)
	@printf "\r$(CY)Generating libft executable...                            $(RC)\n"
	@ ar -rcs $(NAME) $(BONUS_OBJS)
	@printf "$(GR)libft is Ready!$(RC)\n"

.c.o:
	@ $(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	@ $(RM) $(OBJS) $(BONUS_OBJS)
	@printf "$(RE)libft objects removed!$(RC)\n"

fclean:		clean
	@ $(RM) $(NAME)
	@printf "$(RE)libft removed!$(RC)\n"

re :		fclean all

.PHONY:		all clean fclean re bonus
