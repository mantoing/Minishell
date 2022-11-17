# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 19:05:09 by jaeywon           #+#    #+#              #
#    Updated: 2022/11/17 23:53:06 by suhkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
SRC = main.c \
	  push_back.c \
	  push_front.c \
	  init.c \
	  save_env.c \
	  parse.c
OBJ = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft -lreadline \
		#-L/Users/jaeywon/.brew/Cellar/readline/8.2.1/lib \
		-I/Users/jaeywon/.brew/Cellar/readline/8.2.1/include 

.c.o: $(SRC)
	$(CC) $(CFLAGS) -c $^ 
	
clean:
	make -C ./libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME) $(LIBFT)

re:	fclean all
