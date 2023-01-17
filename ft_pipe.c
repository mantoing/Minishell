/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:17:31 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 08:19:26 by suhkim           ###   ########.fr       */
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
	dprintf(2, "in set_pipe\n");
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
	dprintf(2, "open fd : %d %d\n", write_fd[0], write_fd[1]);
}

int	ft_pipe(t_info *info)
{
	t_token	*temp;
	int		i;
	int		pipe_idx;
	int		read_fd[2];
	int		write_fd[2];
	pid_t	pid;
	int		status;

	i = 0;
	pipe_idx = 0;
	pid = 0;
	init_pipe(read_fd, write_fd);
	dprintf(2, "%d %d %d %d\n", read_fd[0], read_fd[1], write_fd[0], write_fd[1]);
	if (!info->input->token_size)
		return (0);
	temp = info->input->head.next;
	while (i <= info->input->token_size)
	{
		if (temp->pipe || temp == &info->input->tail)
		{
			if (temp == &info->input->tail && pipe_idx == 0)
			{
				dprintf(2, "single \n");
				pid = exe_single_cmd(info, temp);
			}
			else
			{
				dprintf(2, "multi\n");
				set_pipe(info, read_fd, write_fd, pipe_idx);
	dprintf(2, "%d %d %d %d\n", read_fd[0], read_fd[1], write_fd[0], write_fd[1]);
				pipe_idx++;
				set_signal("IGNORE");
				pid = fork();
				if (pid == 0)
					ft_token_parse(info, temp, read_fd, write_fd);
				if (info->pipe_cnt > 0)
					info->pipe_cnt--;
			}
			dprintf(2,"what close %d in parents\n", read_fd[0]);
			dprintf(2,"what close %d in parents\n", write_fd[1]);
			ft_close(read_fd[0]);
			ft_close(write_fd[1]);
		}
		temp = temp->next;
		i++;
	}
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
	return (1);
}
