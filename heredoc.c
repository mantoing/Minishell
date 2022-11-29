/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:19:41 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/30 08:15:20 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	valid_heredoc(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

char	*create_temp_file_name(size_t *temp_cnt)
{
	char	*n;
	char	*temp_file_name;
	int		fd;

	n = ft_itoa(*temp_cnt);
	temp_file_name = ft_strjoin("/tmp/minishell_tmp_", n);
	free(n);
	fd = open(temp_file_name, O_RDONLY);
	while (fd >= 0)
	{
		close(fd);
		*temp_cnt += 1;
		free(temp_file_name);
		n = ft_itoa(*temp_cnt);
		temp_file_name = ft_strjoin("/tmp/minishell_tmp_", n);
		free(n);
		fd = open(temp_file_name, O_RDONLY);
	}
	close(fd);
	return (temp_file_name);
}

char	*exe_heredoc(t_token *target, size_t *temp_cnt)
{
	int		fd;
	char	*heredoc_line;
	char	*temp_file_name;

	temp_file_name = create_temp_file_name(temp_cnt);
	fd = open(temp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		heredoc_line = readline("> ");
		if (!heredoc_line)
		{
			//clear_file(fd, tmp_file_path, tmp_file_cnt);
			//error?
			break ;
		}
		if (!ft_strncmp(heredoc_line, target->token, ft_strlen(target->token)))
		{
			free(heredoc_line);
			break ;
		}
		write(fd, ft_strjoin(heredoc_line, "\n"), ft_strlen(heredoc_line) + 1);
		free(heredoc_line);
	}
	close(fd);
	return (temp_file_name);
}

void	change_heredoc_file_name(t_token *arg, char *temp_file_name)
{
	free(arg->token);
	arg->token = ft_strdup(temp_file_name);
	free(temp_file_name);
}
/*
void	write_temp_file(int *fd, char *temp_file_name)
{
	close(fd[0]);
	write(fd[1], ft_strjoin(temp_file_name, "\n"), \
			ft_strlen(temp_file_name) + 1);
	free(temp_file_name);
}
*/

/*
int	check_heredoc(t_info *info)
{
	int		fd[2];
	t_token	*temp;
	pid_t	pid;
	size_t	temp_cnt;

	temp_cnt = 0;
	pipe(fd);
	temp = info->input->head.next;
	pid = fork();
	if (pid == 0)
	{
 		while (temp != &info->input->tail)
 		{
 			if (temp->heredoc)
 			{
 				if (valid_heredoc(info, temp))
					write_temp_file(fd, exe_heredoc(temp->next, &temp_cnt));
 				else
 					return (-1);
 			}
 			temp = temp->next;
 		}
		exit(1);
	}

	return (pid);
}
why fork??
*/
void	check_heredoc(t_info *info)
{
	char	*temp_file_name;
	t_token	*temp;
	size_t	temp_cnt;

	temp_cnt = 0;
	temp = info->input->head.next;
	while (temp != &info->input->tail)
	{
		if (temp->heredoc)
		{
			if (valid_heredoc(info, temp))
			{
				temp_file_name = exe_heredoc(temp->next, &temp_cnt);
				change_heredoc_file_name(temp->next, temp_file_name);
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
	if (WIFSIGNALED(status))
	{
		printf("\n");
		return (1);
	}
	return (0);
}

int	heredoc(t_info *info)
{
	//pid_t	pid;

	check_heredoc(info);
	//wait_heredoc(pid);
	return (1);
}
