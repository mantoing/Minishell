/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:36:15 by jaeywon           #+#    #+#             */
/*   Updated: 2022/11/18 03:45:20 by suhkim           ###   ########.fr       */
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

typedef struct s_input
{
	char	*cmd;
	char	*opt;
	char	*arg;
}	t_input;

typedef struct s_info
{
	t_stack	*env_stack;
	t_input	input;
}	t_info;

int		push_back(t_stack *stack, char *name, char *value);
int		push_front(t_stack *stack, char *name, char *value);
int		save_env(char **env, t_stack *env_stack);
int		init_info(t_info *info);
int		save_env(char **env, t_stack *env_stack);
void	divide_space(t_input *input, char *line);
void	parse(t_info *info, char *line);
char	*get_env(t_info *info, char *name, int *i);
char	*split_quote(t_info *info, char *target);

#endif
