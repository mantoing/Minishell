/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:36:15 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/18 06:11:25 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
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
	char			*home_dir;
	int				exit_code;
	int				pipe_cnt;
}	t_info;

extern int	g_signal;

int		push_back_env(t_stack *stack, char *name, char *value);
int		push_front_env(t_stack *stack, char *name, char *value);
int		push_back_token(t_input *input, char *str);
int		push_front_token(t_input *input, char *str);
int		push_back_unlink(t_unlink *unlink, char *str);
int		push_front_unlink(t_unlink *unlink, char *str);

int		init_info(t_info *info);
void	init_terminal(void);
void	init_input_edge(t_input *input);
int		save_env(char **env, t_info *info);
char	*get_env(t_info *info, char *name, int *i);

int		parse(t_info *info, char *line);
int		ft_pipe(t_info *info);
void	ft_token_parse(t_info *info, t_token *pipe, \
		int *read_fd, int *write_fd);
int		split_token(t_info *info, char *target);
void	del_token(t_input *input, t_token *target, int *arg_size);
void	free_token(t_input *input);
void	free_unlink(t_unlink *unlink);

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

int		heredoc(t_info *info);
void	unlink_all(t_info *info);

int		exe_single_cmd(t_info *info, t_token *temp);
void	exe_builtin(t_info *info, char **arg, int pipe);
int		check_builtin(char *cmd);

char	*check_absol_path(char **arg, t_info *info);

void 	ft_unset(char **arg, t_info *info);
int		ft_pwd(void);
int		ft_export_solo(t_info *info);
int		ft_export_with_arg(t_info *info, char **arg);
int		ft_export(char **arg, t_info *info);
int		ft_env(t_info *info);
int		ft_echo(char **arg);
int		ft_cd(char **arg, t_info *info);
void	ft_exit(t_info *info, char **arg, int pipe);

char	**change_list_to_arr_env(t_info *info);

int		cnt_list_size(t_info *info);
void	free_temp(char **temp);

char	*find_home(t_info *info);

void	sigint_handler(int sig);
void	set_signal(char *type);

void	set_terminal_echo(void);
void	set_terminal_not_echo(void);

int		print_err_with_exit_num(char *s1, char *s2, char *s3, int e_code);
void	print_err(char *s1, char *s2, char *s3);

#endif
