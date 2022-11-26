/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:36:15 by jaeywon           #+#    #+#             */
/*   Updated: 2022/11/27 07:53:50 by suhkim           ###   ########.fr       */
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
	int				heredoc;
	int				redir_r;
	int				redir_l;
	int				append;
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

int		init_info(t_info *info);
int		save_env(char **env, t_stack *env_stack);
char	*get_env(t_info *info, char *name, int *i);

void	parse(t_info *info, char *line);
int		ft_pipe(t_info *info);
void	ft_token_parse(t_info *info, t_token *pipe, int *read_fd, int *write_fd);
int		split_token(t_info *info, char *target);
void	del_token(t_input *input, t_token *target, int *arg_size);
void	free_token(t_input *input);

void	ft_close(int fd);
void	ft_dup2(int fd1, int fd2);

int		get_arg_size(t_info *info, t_token *arg, t_token *pipe);
t_token	*get_first_arg(t_info *info, t_token *pipe);
void	conv_arg(t_token *temp, char **arg, int arg_size);
void	free_arg(char **arg, int arg_size);
int		is_empty_arg(char **arg);
int		cnt_arg_arr_size(char **arg);
char	**arrange_arg(char **arg, int arg_size);

int		redir_l(t_info *info, t_token *pipe);
int		redir_r(t_info *info, t_token *pipe);
int		append(t_info *info, t_token *target);
char	**check_redirection(t_info *info, t_token *pipe);

#endif
