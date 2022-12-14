/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:36:15 by jaeywon           #+#    #+#             */
/*   Updated: 2022/12/24 21:02:15 by suhkim           ###   ########.fr       */
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
# include <termios.h>
# include "./libft/libft.h"

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	char			*env_name;
	char			*env_value;
}	t_node;

typedef struct s_unlink_name
{
	struct s_unlink_name	*next;
	struct s_unlink_name	*prev;
	char					*temp_file_name;
}	t_unlink_name;

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

typedef struct s_unlink
{
	t_unlink_name	head;
	t_unlink_name	tail;
	int				temp_file_cnt;
}	t_unlink;

typedef struct s_info
{
	t_stack			*env_stack;
	t_input			*input;
	t_unlink		*unlink;
	int				pipe_cnt;
}	t_info;


int		push_back_env(t_stack *stack, char *name, char *value);
int		push_front_env(t_stack *stack, char *name, char *value);
int		push_back_token(t_input *input, char *str);
int		push_front_token(t_input *input, char *str);
int		push_back_unlink(t_unlink *unlink, char *str);
int		push_front_unlink(t_unlink *unlink, char *str);

int		init_info(t_info *info);
void	init_terminal(int argc, char **argv);
int		save_env(char **env, t_stack *env_stack);
char	*get_env(t_info *info, char *name, int *i);

void	parse(t_info *info, char *line);
int		ft_pipe(t_info *info);
void	ft_token_parse(t_info *info, t_token *pipe, \
		int *read_fd, int *write_fd);
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
int		redir_append(t_info *info, t_token *target);
char	**check_redirection(t_info *info, t_token *pipe);

int		add_change_export(char **arg, t_info *info);

int		heredoc(t_info *info);
void	unlink_all(t_info *info);

void	exe_single_cmd(t_info *info, t_token *temp);
void	exe_builtin(t_info *info, char **arg);
int		check_builtin(char *cmd);

char	*check_absol_path(char **arg, t_info *info);

void 	ft_unset(char **arg, t_info *info);
int		ft_pwd(void);
int		ft_export_solo(t_info *info);
int		ft_export(char **arg, t_info *info);
int		ft_env(t_info *info);
int		ft_echo(char **arg);
int		ft_cd(char **arg, t_info *info);

char	**change_list_to_arr_env(t_info *info);

int		cnt_list_size(t_info *info);
void	free_temp(char **temp);

char	*find_home(t_info *info);

void	sigint_handler(int sig);
void	set_signal(char *type);

#endif
