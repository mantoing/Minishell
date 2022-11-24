/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:17:31 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/25 01:14:33 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	init_pipe(int *read_fd, int *write_fd)
{
	read_fd[0] = STDIN_FILENO;
	//read_fd[0] = 0; same?
	read_fd[1] = -1;
	write_fd[0] = -1;
	write_fd[1] = STDOUT_FILENO;
	//write_fd[1] = 1; same?
}

void	set_pipe(t_info *info, int *read_fd, int *write_fd)
{
	if (info->pipe_cnt == 0)
	{
		write_fd[0] = -1;
		write_fd[1] = STDOUT_FILENO;
	}
	else
	{
		read_fd[0] = write_fd[0];
		read_fd[1] = write_fd[1];
	}
	if (info->pipe_cnt)
		pipe(write_fd);
}

int	ft_pipe(t_info *info)
{
	t_token	*temp;
	int		i;
	int		read_fd[2];
	int		write_fd[2];

	i = 0;
	init_pipe(read_fd, write_fd);
	temp = info->input->head.next;
	while (i <= info->input->token_size)
	{
		if (temp->pipe || temp == &info->input->tail)
		{
			set_pipe(info, read_fd, write_fd);
			ft_fork(info, temp, read_fd, write_fd);
			info->pipe_cnt--;
		}
		temp = temp->next;
		i++;
	}
	return (1);
}
