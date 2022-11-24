/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:52:42 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/25 06:27:19 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	conv_arg(t_token *temp2, char **arg, int arg_size)
{
	int	i;

	i = 0;
	while (i < arg_size)
	{
		*(arg + i) = ft_strdup(temp2->token);
		temp2 = temp2->next;
		i++;
	}
	*(arg + i) = NULL;
}

int	ft_fork(t_info *info, t_token *pipe, int *read_fd, int *write_fd)
{
	t_token	*temp;
	t_token	*temp2;
	char	**arg;
	int		arg_size;
	pid_t	pid;

	(void)read_fd;
	(void)write_fd;
	arg_size = 0;
	temp = pipe->prev;
	while (temp->prev != &info->input->head && !temp->prev->pipe)
		temp = temp->prev;
	temp2 = temp;
	while (temp != &info->input->tail && temp != pipe)
	{
		arg_size++;
		temp = temp->next;
	}
	pid = fork();
	if (pid == 0)
	{
		arg = malloc(sizeof(char *) * (arg_size + 1));
		if (!arg)
			return (0);
		conv_arg(temp2, arg, arg_size);
		//exe_cmd(info, arg, read_fd, write_fd);
	}
	if (pid == 0)
	{
		if (!ft_strncmp("echo", *(arg), ft_strlen(*(arg))))
		{
			ft_close(read_fd[1]);
			ft_close(write_fd[0]);
			ft_dup2(read_fd[0], STDIN_FILENO);
			ft_dup2(write_fd[1], STDOUT_FILENO);
			printf("echo %d %d\n", read_fd[0], write_fd[1]);
			execve("/bin/echo", arg, NULL);
		}
		else if (!ft_strncmp("ls", *(arg), ft_strlen(*(arg))))
		{
			ft_close(read_fd[1]);
			ft_close(write_fd[0]);
			ft_dup2(read_fd[0], STDIN_FILENO);
			ft_dup2(write_fd[1], STDOUT_FILENO);
			printf("ls %d %d\n", read_fd[0], write_fd[1]);
			execve("/bin/ls", arg, NULL);
		}
		else if (!ft_strncmp("cat", *(arg), ft_strlen(*(arg))))
		{
			ft_close(read_fd[1]);
			ft_close(write_fd[0]);
			ft_dup2(read_fd[0], STDIN_FILENO);
			ft_dup2(write_fd[1], STDOUT_FILENO);
			printf("cat %d %d\n", read_fd[0], write_fd[1]);
			execve("/bin/cat", arg, NULL);
		}
		exit(1);
	}
	return (pid);
}
