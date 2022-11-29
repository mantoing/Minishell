/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:52:42 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/30 08:53:36 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_token_parse(t_info *info, t_token *pipe, int *read_fd, int *write_fd)
{
	//t_token	*temp;
	char	**arg;

//	arg_size = 0;
//	temp = pipe->prev;
//	while (temp->prev != &info->input->head && !temp->prev->pipe)
//		temp = temp->prev;
//	temp2 = temp;
//	while (temp != &info->input->tail && temp != pipe)
//	{
//		arg_size++;
//		temp = temp->next;
//	}
	ft_close(read_fd[1]);
	ft_close(write_fd[0]);
	ft_dup2(read_fd[0], STDIN_FILENO);
	ft_dup2(write_fd[1], STDOUT_FILENO);
	//dprintf(2,"before redir_r\n");
	//arg = redir_r(info, pipe);
	arg = check_redirection(info, pipe);
	//dprintf(2,"exe_cmd\n");
//	temp = get_first_arg(info, pipe);
//	arg_size = get_arg_size(info, temp, pipe);
//	arg = malloc(sizeof(char *) * (arg_size + 1));
//	conv_arg(temp, arg, arg_size);
	//exe_cmd(info, arg, read_fd, write_fd);
	if (!is_empty_arg(arg))
	{
			//return free_arg(arg, 0);
		if (!ft_strncmp("echo", *(arg), ft_strlen(*(arg))))
		{
	//		ft_close(read_fd[1]);
	//		ft_close(write_fd[0]);
	//		ft_dup2(read_fd[0], STDIN_FILENO);
	//		ft_dup2(write_fd[1], STDOUT_FILENO);
			//dprintf(2,"echo %d %d\n", read_fd[0], write_fd[1]);
			execve("/bin/echo", arg, NULL);
		}
		else if (!ft_strncmp("ls", *(arg), ft_strlen(*(arg))))
		{
	//		ft_close(read_fd[1]);
	//		ft_close(write_fd[0]);
	//		ft_dup2(read_fd[0], STDIN_FILENO);
	//		ft_dup2(write_fd[1], STDOUT_FILENO);
			//dprintf(2,"ls %d %d\n", read_fd[0], write_fd[1]);
			execve("/bin/ls", arg, NULL);
		}
		else if (!ft_strncmp("cat", *(arg), ft_strlen(*(arg))))
		{
	//		ft_close(read_fd[1]);
	//		ft_close(write_fd[0]);
	//		ft_dup2(read_fd[0], STDIN_FILENO);
	//		ft_dup2(write_fd[1], STDOUT_FILENO);
			//dprintf(2,"cat %d %d\n", read_fd[0], write_fd[1]);
			execve("/bin/cat", arg, NULL);
		}
		else if (!ft_strncmp("./a.out", *(arg), ft_strlen(*(arg))))
		{
			execve("./a.out", arg, NULL);
		}
	}
	if (arg)
		free_arg(arg, cnt_arg_arr_size(arg));
	exit(1);
}
