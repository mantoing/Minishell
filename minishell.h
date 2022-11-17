/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:36:15 by jaeywon           #+#    #+#             */
/*   Updated: 2022/11/17 23:19:55 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	char			*env_name;
	char			*env_value;
}	t_node;

typedef struct s_stack
{
	t_node	head;
	t_node	tail;
	int		size;
}	t_stack;

int		push_back(t_stack *stack, char *name, char *value);
int		push_front(t_stack *stack, char *name, char *value);
int		save_env(char **env, t_stack *env_stack);
void	init_stack(t_stack *stack);
int		save_env(char **env, t_stack *env_stack);
void	parse(char *line);

#endif
