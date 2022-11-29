# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 19:05:09 by jaeywon           #+#    #+#              #
#    Updated: 2022/11/30 08:20:29 by suhkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
SRC = main.c \
	  push_back_token.c \
	  push_front_token.c \
	  push_back_env.c \
	  push_front_env.c \
	  init.c \
	  save_env.c \
	  parse.c \
	  split_token.c \
	  get_env.c \
	  free_token.c \
	  ft_token_parse.c \
	  ft_pipe.c \
	  ft_dup2.c \
	  ft_close.c \
	  check_redirection.c \
	  redir_r.c \
	  redir_l.c \
	  redir_append.c \
	  arg_utils.c \
	  arg_utils2.c \
	  del_token.c \
	  heredoc.c	\
	  unlink.c

OBJ = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft -lreadline 

.c.o: $(SRC)
	@$(CC) $(CFLAGS) -c $^ 
	
clean:
	@make -C ./libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C ./libft fclean
	@$(RM) $(NAME) $(LIBFT)

re:	fclean all

.PHONY = all, clean, fclean, re
