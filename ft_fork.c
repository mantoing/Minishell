/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:52:42 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/25 01:52:16 by suhkim           ###   ########.fr       */
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
	int		status;
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
//	if (pid == 0)
//	{
//		if (!ft_strncmp(*(arg), "echo", 4))
//		{
//		//	printf("\n i'm echo \n");
//			execve("/bin/echo", arg, NULL);
//		}
//		exit(1);
//	}
//	else
//	{
//		pid = wait(&status);
//	}
	return (1);
}
