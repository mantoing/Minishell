# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 19:05:09 by jaeywon           #+#    #+#              #
#    Updated: 2022/11/16 19:59:34 by jaeywon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c
OBJ = $(SRC:.c=.o)
RM = /bin/rm -f

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft -lreadline \
		-L/Users/jaeywon/.brew/Cellar/readline/8.2.1/lib \
		-I/Users/jaeywon/.brew/Cellar/readline/8.2.1/include 

.c.o: $(SRC)
	$(CC) $(CFLAGS) -c $^ 
	
clean:
	$(RM) WITH_B=1 $(OBJ)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re:	fclean all