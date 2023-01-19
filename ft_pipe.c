/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:17:31 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 17:56:26 by jaeywon          ###   ########.fr       */
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

static void	handle_e_code(t_info *info, pid_t pid)
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
	set_signal("SHELL");
}

int	ft_pipe(t_info *info)
{
	t_token	*temp;
	int		i;
	int		pipe_idx;
	int		read_fd[2];
	int		write_fd[2];
	pid_t	pid;

	i = 0;
	pipe_idx = 0;
	pid = 0;
	init_pipe(read_fd, write_fd);
	if (!info->input->token_size)
		return (0);
	temp = info->input->head.next;
	while (i <= info->input->token_size)
	{
		if (temp->pipe || temp == &info->input->tail)
		{
			if (temp == &info->input->tail && pipe_idx == 0)
				pid = exe_single_cmd(info, temp);
			else
			{
				set_pipe(info, read_fd, write_fd, pipe_idx);
				pipe_idx++;
				set_signal("IGNORE");
				pid = fork();
				if (pid == 0)
					ft_token_parse(info, temp, read_fd, write_fd);
				if (info->pipe_cnt > 0)
					info->pipe_cnt--;
			}
			ft_close(read_fd[0]);
			ft_close(read_fd[1]);
		}
		temp = temp->next;
		i++;
	}
	handle_e_code(info, pid);
	return (1);
}
