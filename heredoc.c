/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:19:41 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 07:01:54 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	valid_heredoc(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

static char	*create_temp_file_name(size_t *temp_cnt)
{
	char	*n;
	char	*temp_file_name;
	int		fd;

	n = ft_itoa(*temp_cnt);
	temp_file_name = ft_strjoin(ft_strdup("/tmp/minishell_tmp_"), n);
	fd = open(temp_file_name, O_RDONLY);
	while (fd >= 0)
	{
		close(fd);
		*temp_cnt += 1;
		free(temp_file_name);
		n = ft_itoa(*temp_cnt);
		temp_file_name = ft_strjoin(ft_strdup("/tmp/minishell_tmp_"), n);
		fd = open(temp_file_name, O_RDONLY);
	}
	close(fd);
	return (temp_file_name);
}

static void	exe_heredoc(t_token *target, size_t *temp_cnt)
{
	int		fd;
	char	*heredoc_line;
	char	*temp_file_name;

	temp_file_name = create_temp_file_name(temp_cnt);
	fd = open(temp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(temp_file_name);
	set_signal("HEREDOC");
	while (1)
	{
		heredoc_line = readline("> ");
		if (!heredoc_line)
			break ;
		if (!ft_strcmp(heredoc_line, target->token))
		{
			free(heredoc_line);
			break ;
		}
		write(fd, ft_strjoin(heredoc_line, ft_strdup("\n")),\
				ft_strlen(heredoc_line) + 1);
	}
	close(fd);
}


static int	check_heredoc(t_info *info)
{
	int		fd[2];
	t_token	*temp;
	pid_t	pid;
	size_t	temp_cnt;

	temp_cnt = 0;
	pipe(fd);
	temp = info->input->head.next;
	set_signal("IGNORE");
	pid = fork();
	if (pid == 0)
	{
 		while (temp != &info->input->tail)
 		{
 			if (temp->heredoc)
 			{
 				if (valid_heredoc(info, temp))
				{
					exe_heredoc(temp->next, &temp_cnt);
					temp_cnt += 1;
				}
 				else
 					return (-1);
 			}
 			temp = temp->next;
 		}
		exit(0);
	}
	return (pid);
}

static void	save_temp_num(t_info *info)
{
	t_token	*temp;
	size_t	temp_cnt;

	temp_cnt = 0;
	temp = info->input->head.next;
 	while (temp != &info->input->tail)
	{
		if (temp->heredoc)
			if (valid_heredoc(info, temp))
			{
				push_back_unlink(info->unlink, \
						create_temp_file_name(&temp_cnt));
				temp_cnt += 1;
			}
 		temp = temp->next;
 	}
}

static void	change_heredoc_file_name(t_token *arg, char *temp_file_name)
{
	free(arg->token);
	arg->token = ft_strdup(temp_file_name);
}

static void	change_arg_temp_file(t_info *info)
{
	t_token			*temp;
	t_unlink_name	*temp_unlink;
	size_t			temp_cnt;

	temp_cnt = 0;
	temp = info->input->head.next;
	temp_unlink = info->unlink->head.next;
	while (temp != &info->input->tail)
	{
		if (temp->heredoc)
		{
			if (valid_heredoc(info, temp))
			{
				change_heredoc_file_name(temp->next, \
				temp_unlink->temp_file_name);
				temp_unlink = temp_unlink->next;
			}
			else
				return ;
		}
		temp = temp->next;
	}
}

int	wait_heredoc(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	if (WIFSIGNALED(status))
	{
		printf("\n");
		return (0);
	}
	return (1);
}

int	heredoc(t_info *info)
{
	pid_t	pid;
	int		ifsignal;

	g_signal = 0;
	save_temp_num(info);
	pid = check_heredoc(info);
	set_signal("HEREDOCWAIT");
	ifsignal = wait_heredoc(pid);
	change_arg_temp_file(info);
	set_signal("SHELL");
	return (ifsignal);
}
