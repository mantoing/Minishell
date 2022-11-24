/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:36:15 by jaeywon           #+#    #+#             */
/*   Updated: 2022/11/25 06:09:37 by suhkim           ###   ########.fr       */
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

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	int				pipe;
	char			*token;
}	t_token;

typedef struct s_input
{
	t_token	head;
	t_token	tail;
	int		token_size;
}	t_input;

typedef struct s_info
{
	t_stack	*env_stack;
	t_input	*input;
	int		pipe_cnt;

}	t_info;

int		push_back_env(t_stack *stack, char *name, char *value);
int		push_front_env(t_stack *stack, char *name, char *value);
int		push_back_token(t_input *input, char *str);
int		push_front_token(t_input *input, char *str);

int		save_env(char **env, t_stack *env_stack);
int		init_info(t_info *info);
int		save_env(char **env, t_stack *env_stack);
void	divide_space(t_input *input, char *line);
void	parse(t_info *info, char *line);
int		ft_pipe(t_info *info);
int		ft_fork(t_info *info, t_token *pipe, int *read_fd, int *write_fd);
char	*get_env(t_info *info, char *name, int *i);
int		split_token(t_info *info, char *target);
void	free_token(t_input *input);
void	ft_close(int fd);
void	ft_dup2(int fd1, int fd2);

#endif
