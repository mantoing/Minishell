/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:17:31 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 20:01:38 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	init_pipe(int *read_fd, int *write_fd)
{
	read_fd[0] = STDIN_FILENO;
	read_fd[1] = -1;
	write_fd[0] = -1;
	write_fd[1] = STDOUT_FILENO;
}

void	set_pipe(t_info *info, int *read_fd, int *write_fd, int pipe_idx)
{
	if (pipe_idx != 0)
	{
		read_fd[0] = write_fd[0];
		read_fd[1] = write_fd[1];
	}
	if (info->pipe_cnt == 0)
	{
		write_fd[0] = -1;
		write_fd[1] = STDOUT_FILENO;
	}
	if (info->pipe_cnt)
		pipe(write_fd);
}

void	check_status(t_info *info, pid_t pid)
{
	int	status;

	if (pid)
	{
		waitpid(pid, &status, 0);
		while (waitpid(-1, 0, 0) != -1)
			;
		if (WIFEXITED(status))
			info->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			info->exit_code = WTERMSIG(status) + 128;
	}
}

pid_t	in_pipe(t_info *info, t_token *temp, int *pipe_idx, t_fd *fd)
{
	pid_t	pid;

	pid = 0;
	if (temp->pipe || temp == &info->input->tail)
	{
		if (temp == &info->input->tail && *pipe_idx == 0)
			pid = exe_single_cmd(info, temp);
		else
		{
			set_pipe(info, fd->read_fd, fd->write_fd, *pipe_idx);
			*pipe_idx += 1;
			set_signal("IGNORE");
			pid = fork();
			if (pid == 0)
				ft_token_parse(info, temp, fd->read_fd, fd->write_fd);
			if (info->pipe_cnt > 0)
				info->pipe_cnt--;
		}
		ft_close(fd->read_fd[0]);
		ft_close(fd->read_fd[1]);
	}
	return (pid);
}

int	ft_pipe(t_info *info)
{
	t_token	*temp;
	int		i;
	int		pipe_idx;
	t_fd	fd;
	pid_t	pid;

	i = 0;
	pipe_idx = 0;
	pid = 0;
	init_pipe(fd.read_fd, fd.write_fd);
	if (!info->input->token_size)
		return (0);
	temp = info->input->head.next;
	while (i <= info->input->token_size)
	{
		if (temp->pipe || temp == &info->input->tail)
			pid = in_pipe(info, temp, &pipe_idx, &fd);
		temp = temp->next;
		i++;
	}
	check_status(info, pid);
	set_signal("SHELL");
	return (1);
}
