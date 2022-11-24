/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:17:31 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/25 06:55:37 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	init_pipe(int *read_fd, int *write_fd)
{
	//read_fd[0] = STDIN_FILENO;
	read_fd[0] = 0;
	read_fd[1] = -1;
	write_fd[0] = -1;
	//write_fd[1] = STDOUT_FILENO;
	write_fd[1] = 1;
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

/*
void	wait_last_process(pid_t pid, int *flag)
{
	int	status;

	status = 0;
	*flag = 0;
	waitpid(pid, &status, 0);
}

void	wait_child_process(pid_t pid)
{
	int	status;
	int	flag;

	wait_last_process(pid, &flag);
	status = 0;
	while (wait(&status) != -1)
		;
}
*/

int	ft_pipe(t_info *info)
{
	t_token	*temp;
	int		i;
	int		pipe_idx;
	int		read_fd[2];
	int		write_fd[2];
	pid_t	test;
	int		status;

	i = 0;
	pipe_idx = 0;
	init_pipe(read_fd, write_fd);
	temp = info->input->head.next;
	while (i <= info->input->token_size)
	{
		if (temp->pipe || temp == &info->input->tail)
		{
			set_pipe(info, read_fd, write_fd, pipe_idx);
			pipe_idx++;
			/*
			if (info->pipe_cnt == 0)
			{
				printf("read echo = %d %d\n", read_fd[0], read_fd[1]);
			}
			else
			{
				printf("read ls = %d %d\n", read_fd[0], read_fd[1]);
			}
			*/
			test = ft_fork(info, temp, read_fd, write_fd);
			if (info->pipe_cnt > 0)
				info->pipe_cnt--;
			ft_close(read_fd[0]);
			ft_close(read_fd[1]);
		}
		waitpid(test, &status, 0);
		temp = temp->next;
		i++;
	}
	return (1);
}
